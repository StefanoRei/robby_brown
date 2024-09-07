#pragma platform(NXT)

//
// Function and task prototypes
//
task checkBTLinkConnected();// task for check connection with arduino
task Display_data();//task for output data on dispay
task bt_Recieve_data_task(); /// task for recieve byte from arduino and save it in global variable

task bt_Send_data_task(); /// task for send byte to arduino global variable send_data[1]
                          /// task automated send variale send_data[1] each Background_Send_data_interval in ms to arduino.
                          /// If need send - use special function - see below.

////Global variables for BT
bool finish_prog_bt = false; /// have true value when BT module on arduino is offline and disconnected or no paired

///// Sending data global variables
ubyte send_data[1]; /// byte for send to arduino
bool Send_data_start = false; /// set to true for start sending process emmideatly
bool Send_busy = false; /// have true value if sending process is active
ubyte sended = 0; /// have 1 vakue if sending process was done
int Background_Send_data_interval = 1000; /// interval in ms between auto sending current send byte to arduino
long int sended_number = 0; /// number of sending bytes



///// Recieving data global variables
bool Recieve_flag = false; ///have true value when byte recieved - need for check connection in checkBTLinkConnected() task
bool Recieve_error = false;///have true value when 5sec data not recieved
ubyte recieve_data = 0; /// last recieved byte
long int recieved_number = 0;/// number of recieved bytes

//// function for write data1 byte to sending byte for send to arduino
//// Sending will do in background task each background sending interval
void bt_send_data(ubyte data1)
{
 if (finish_prog_bt == true) return; //// if bt module is not connected - return without any doing

 int pause = 0;

 //// cycle for waiting if sending task is busy
 //// waiting 2 seconds. if waiting time is over 2 seconds - sended value is 0, sending have error
 while (pause<2000) {
  	if ((Send_busy == false) && (Send_data_start==false)) {
  		pause = 3000;
  	} else {
    	wait1Msec(1);
    	pause = pause + 1;
  	}
  }
  if (pause == 3000) { /// when sending task not busy
	    send_data[0] = data1; /// copy data1 to send byte using sending task
	                          /// sending task will automated send it in Background_Send_data_interval to arduino
	    sended = 1; /// sending is good
  } else {
    sended = 0; /// if sending task is busy over 2 seconds.
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Tasks
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
task checkBTLinkConnected() /// check bt errors
{

  clearTimer(T4);
  clearTimer(T1);
  clearTimer(T3);

  while (true)
	{
		if (nBTCurrentStreamIndex < 0) //// check for arduino module is paired and connected to nxt
		{	//
			// Not connected. Audible notification each 5 seconds and LCD error display in display task
			//
		  if (time1[T3]>5000)
		     {
		       playSound(soundLowBuzz);
		       ///soundBeepBeep
		       clearTimer(T3);
		     }
		  finish_prog_bt=true;

		}
		else
			 {//// if arduino bt module is connected
			   finish_prog_bt=false; /// do not show lcd error message
			   clearTimer(T3);

         if (Recieve_flag == true) { /// if byte is recieved - clear timers and clear error.
           clearTimer(T1);/// clear waiting timer
           clearTimer(T4);/// clear timer for sound when recieve error
           Recieve_flag = false; /// set up flag to false and waiting new recieved byte
           Recieve_error = false; /// error is false
     		 }

         if (time1[T1]>5000) /// if byte not recieved over 5 seconds
    		   {
             Recieve_error = true; /// set up error flag for display task
             if (time1[T4]>1000) /// play sound each 1 seconds
		          {
     		       playSound(soundBlip);
       	       clearTimer(T4);
     		      }
 	         } else {
              clearTimer(T4);

           }
       }

		wait1Msec(1);
  }
}

//// task for output all base variables and error messages to display
//// in real time
task Display_data()
{
	while (true)
	{
		if (finish_prog_bt==false) /// bt arduino module is connected
	  {
		   nxtDisplayTextLine(0, "R %d ", recieve_data); /// show last recieved byte
		   nxtDisplayTextLine(1, "R num %d ", recieved_number); /// show number of reciceved bytes


		   nxtDisplayTextLine(3, "S %d ", send_data); /// show last sending byte
       nxtDisplayTextLine(4, "S num %d ", sended_number); /// show number of sended bytes


     if (sended==1) {nxtDisplayTextLine(5,"Sended ok");} else {nxtDisplayTextLine(5,"Send is busy.");} //// show message if sending process busy long time

     //// show error message if recieving is not done over 5 seconds
     if (Recieve_error == false) {
        nxtDisplayTextLine(6,"No link error");
     } else {
        nxtDisplayTextLine(6,"Recieve error");
     }

     }
	  else //// if arduino bt module is not connected - show error message
	  {
      eraseDisplay();
  		nxtDisplayTextLine(1, "BT not connected");
  		wait1Msec(100);
    }
		wait1Msec(100);
	}
}


///// recieve task
//// work in background and write last reciceved byte
//// to recieve_data variable
task bt_Recieve_data_task()
{
  ubyte BytesRead[1]; // Buffer of last byte read. Waiting only one byte.
  int nNumbBytesRead; /// number of bytes recieved from bt.
  while (true)
   {
      if (finish_prog_bt==false) /// if arduino module is connected
       {
           nNumbBytesRead = nxtReadRawBluetooth(BytesRead, sizeof(BytesRead)); /// reading number of bytes recieved from bt
           if (nNumbBytesRead == 0) /// if number of bytes = 0 (bytes not recieved)
            {
              wait1Msec(1);// wait for 1 ms between jumping to start new iteration
              continue; /// jump to start new iteration of cycle while(true), all next program strings for this cycle not running
            }
           Recieve_flag = true; /// if number of bytes not equal zero
           recieve_data = BytesRead[0]; // reading first recieved byte from bt
           recieved_number++; /// add 1 to number of recieved bytes
       }
    wait1Msec(1); /// wait 1ms between iteration of cycle while(true)
   }
}


//// sending task
/// work in background
/// auto send last sending byte to arduino each Background_Send_data_interval in ms
/// can send sending byte emmideatly by set Send_data_start flag to true
task bt_Send_data_task()
{
	/// init values
	clearTimer(T2); /// clear backround time interval - only one times when task is starting

	while (true)
	{
   if (finish_prog_bt==false)/// if bt arduino moduleis connected
    {
      if (Send_data_start==true) // if need sending emmideatly
		   {
        Send_busy = true; /// set up busy flag
        nxtWriteRawBluetooth(nBTCurrentStreamIndex , send_data, sizeof(send_data)); /// send to bt
        sended_number++; /// add number of sended bytes
        clearTimer(T2);/// clear background timer
        Send_data_start = false; /// clear flag for emmideatly sending
        Send_busy = false; /// clear busy flag
		   }	else { /// if background sending
			  if (time1[T2]>Background_Send_data_interval)/// if timer is over background time interval
		     {  Send_busy = true;/// set up busy flag
              nxtWriteRawBluetooth(nBTCurrentStreamIndex , send_data, sizeof(send_data)); /// send to bt
              sended_number++; /// add number of sended bytes
		          clearTimer(T2);/// clear background timer
              Send_busy = false;/// clear busy flag
         }
		   }
    } else { /// if bt arduino module not connected
	   clearTimer(T2);/// clear background timer
     Send_busy = false; /// clear busy flag
     Send_data_start = false; /// clear sending flag
    }
   wait1Msec(1); /// wait 1ms between iterations of cycle while(true)
 }
}


ubyte a1 = 0; /// variable for bt example program


////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                       Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
task main()
{
	//
	// Test Ability to Turn Bluetooth On
	//
 while(bBTBusy)// while the Bluetooth is busy (bBTBusy == true):
 {
 nxtDisplayCenteredTextLine(3, "BT busy");   // display, "BT is BUSY" in big, centered type
 wait1Msec(100);                                   // wait 100 milliseconds (helps display correctly)
 }

 setBluetoothOn(); /// set up bt in nxt on, if already on - do nothing

 //// wait command is done
	while(bBTBusy)// while the Bluetooth is busy (bBTBusy == true):
 {
 nxtDisplayCenteredTextLine(3, "BT is BUSY for start");   // display, "BT is BUSY", centered type
 wait1Msec(100);                                          // wait 100 milliseconds (helps display correctly)
 }

 btDisconnectAll(); // if bt was already on, disconnect all remote bt modules connected to nxt, if only now switch on - do nothing

 /// wait command is done
 	while(bBTBusy)// while the Bluetooth is busy (bBTBusy == true):
 {
 nxtDisplayCenteredTextLine(3, "disconnect all");   // display, "BT is BUSY" in big, centered type
 wait1Msec(100);                                   // wait 100 milliseconds (helps display correctly)
 }

 btConnect(2, "ROBBY"); /// connect to saved in nxt slot 2 paired remote module with name "ROBBY"
 //// arduino module must paired with nxt in slot 2 by manual, and it must named "ROBBY"

 /// wait command is done
 while(bBTBusy)// while the Bluetooth is busy (bBTBusy == true):
 {
 nxtDisplayCenteredTextLine(3, "connect robby");   // display, "BT is BUSY" in big, centered type
 wait1Msec(100);                                   // wait 100 milliseconds (helps display correctly)
 }

 wait1Msec(1000); /// wait 1 second for all needed pauses

 setBluetoothRawDataMode(); /// set up nxt bt module in raw mode - sending and recieve bytes, not lego messages

 /// wait is switching was done
 while (!bBTRawMode)
{
  wait1Msec(100);
}

 wait1Msec(1000); /// wait 1 second for all needed pauses

 //// starting all background tasks
  startTask(checkBTLinkConnected);
	startTask(Display_data);
	startTask(bt_Recieve_data_task);
	startTask(bt_Send_data_task);



//// example for change value of sending byte to arduino each 1750ms
//// remember, that background task auto sending this byte by each 1 second (background sending time interval)

 while (true)
	{
    wait1Msec(1750);
    bt_send_data(a1);
    a1++;
    if (a1>253) a1=0;
	}




}
