#include <public/ccobsmng_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCObsMng::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CCObsMng &act,
	 Pr_Time & EDROOMpVarVNextTimeOut ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	ObsMng(EDROOMcomponent.ObsMng),
	ObservTimer(EDROOMcomponent.ObservTimer),
	AttCtrlTimer(EDROOMcomponent.AttCtrlTimer),
	CImageInterval(0,5),
	VNextTimeOut(EDROOMpVarVNextTimeOut)
{
}

CCObsMng::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	ObsMng(context.ObsMng),
	ObservTimer(context.ObservTimer),
	AttCtrlTimer(context.AttCtrlTimer),
	CImageInterval(0,5),
	VNextTimeOut(context.VNextTimeOut)
{

}

	// EDROOMSearchContextTrans********************************************

bool CCObsMng::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
			TEDROOMTransId &edroomCurrentTrans)
			{

	bool edroomValidMsg=false; 

	 switch(Msg->signal)
	{

		 case ( EDROOMSignalDestroy ): 

			 edroomValidMsg=true;
			 edroomCurrentTrans.distanceToContext = 0 ;
			 edroomCurrentTrans.localId = -1 ;
			 break;

	}

	return(edroomValidMsg);

}

	// User-defined Functions   ****************************

void	CCObsMng::EDROOM_CTX_Top_0::FDoAttitudeCtrl()

{

pus_service129_do_attitude_ctrl();

}



void	CCObsMng::EDROOM_CTX_Top_0::FEndObservation()

{

VNextTimeOut.GetTime();
pus_service129_end_observation();

}



void	CCObsMng::EDROOM_CTX_Top_0::FInit()

{
   //Define absolute time
  Pr_Time time;

  //Timing Service useful methods

	time.GetTime(); // Get current monotonic time
	time+=Pr_Time(0,100000); // Add X sec + Y microsec

   //Program absolute timer
   AttCtrlTimer.InformAt( time );
}



void	CCObsMng::EDROOM_CTX_Top_0::FProgAttitudeCtrl()

{
   //Define absolute time
  Pr_Time time;
	 
//Timing Service useful methods
	 
	time.GetTime(); // Get current monotonic time
	time+=Pr_Time(0,100000); // Add X sec + Y microsec
 
   //Program absolute timer 
   AttCtrlTimer.InformAt( time ); 
}



void	CCObsMng::EDROOM_CTX_Top_0::FProgTakeImage()

{
   //Define interval
  Pr_Time interval;
interval=CImageInterval;
   //Program relative timer 
   ObservTimer.InformIn( interval ); 
}



void	CCObsMng::EDROOM_CTX_Top_0::FTakeImage()

{

pus_service129_take_image();

}



void	CCObsMng::EDROOM_CTX_Top_0::FToObservation()

{

pus_service129_start_observation();

}



bool	CCObsMng::EDROOM_CTX_Top_0::GLastImage()

{

return pus_service129_is_last_image();

}



bool	CCObsMng::EDROOM_CTX_Top_0::GReadyToObservation()

{

return pus_service129_is_observation_ready();

}



void	CCObsMng::EDROOM_CTX_Top_0::FExecObsMng_TC()

{
   //Handle Msg->data
  CDTCHandler & varSObsMng_TC = *(CDTCHandler *)Msg->data;
	
// Data access
	
varSObsMng_TC.ExecTC();

}



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCObsMng::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CCObsMng&act):
		EDROOM_CTX_Top_0(act,
			VNextTimeOut),
		VNextTimeOut()
{

}

	//***************************** EDROOMBehaviour ********************************

void CCObsMng::EDROOM_SUB_Top_0::EDROOMBehaviour()
{

	TEDROOMTransId edroomCurrentTrans;

	//Behaviour starts from Init State

	edroomCurrentTrans = EDROOMIArrival();

	do
	{

		//Take next transition

		switch(edroomCurrentTrans.localId)
		{

			//Next Transition is Init
			case (Init):
				//Execute Action 
				FInit();
				//Next State is Standby
				edroomNextState = Standby;
				break;
			//To Choice Point ToChoicePoint
			case (ToChoicePoint):

				//Execute Action 
				FDoAttitudeCtrl();
				//Evaluate Branch ToNewObservation
				if( GReadyToObservation() )
				{
					//Execute Action 
					FToObservation();

					//Branch taken is ToChoicePoint_ToNewObservation
					edroomCurrentTrans.localId =
						ToChoicePoint_ToNewObservation;

					//Next State is NewObservation
					edroomNextState = NewObservation;
				 } 
				//Default Branch PorgAttitude
				else
				{
					//Execute Action 
					FProgAttitudeCtrl();

					//Branch taken is ToChoicePoint_PorgAttitude
					edroomCurrentTrans.localId =
						ToChoicePoint_PorgAttitude;

					//Next State is Standby
					edroomNextState = Standby;
				 } 
				break;
			//To Choice Point TakeImage
			case (TakeImage):

				//Execute Action 
				FTakeImage();
				//Evaluate Branch ToStandby
				if( GLastImage() )
				{
					//Execute Actions 
					FEndObservation();
					FProgAttitudeCtrl();

					//Branch taken is TakeImage_ToStandby
					edroomCurrentTrans.localId =
						TakeImage_ToStandby;

					//Next State is Standby
					edroomNextState = Standby;
				 } 
				//Default Branch ToObservationAgain
				else
				{

					//Branch taken is TakeImage_ToObservationAgain
					edroomCurrentTrans.localId =
						TakeImage_ToObservationAgain;

					//Next State is NewObservation
					edroomNextState = NewObservation;
				 } 
				break;
			//Next Transition is ExecTcs
			case (ExecTcs):
				//Msg->Data Handling 
				FExecObsMng_TC();
				//Next State is Standby
				edroomNextState = Standby;
				break;
		}

		//Entry into the Next State 
		switch(edroomNextState)
		{

				//Go to the state I
			case (I):
				//Arrival to state I
				edroomCurrentTrans=EDROOMIArrival();
				break;

				//Go to the state Standby
			case (Standby):
				//Arrival to state Standby
				edroomCurrentTrans=EDROOMStandbyArrival();
				break;

				//Go to the state NewObservation
			case (NewObservation):
				//Execute Entry Action 
				FProgTakeImage();
				//Arrival to state NewObservation
				edroomCurrentTrans=EDROOMNewObservationArrival();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Context Init**********************************************

void CCObsMng::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCObsMng::EDROOM_SUB_Top_0::EDROOMIArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Standby

	// ***********************************************************************



TEDROOMTransId CCObsMng::EDROOM_SUB_Top_0::EDROOMStandbyArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (EDROOMSignalTimeout): 

				 if (*Msg->GetPInterface() == AttCtrlTimer)
				{

					//Next transition is  ToChoicePoint
					edroomCurrentTrans.localId = ToChoicePoint;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

			case (SObsMng_TC): 

				 if (*Msg->GetPInterface() == ObsMng)
				{

					//Next transition is  ExecTcs
					edroomCurrentTrans.localId= ExecTcs;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

		};

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  NewObservation

	// ***********************************************************************



TEDROOMTransId CCObsMng::EDROOM_SUB_Top_0::EDROOMNewObservationArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (EDROOMSignalTimeout): 

				 if (*Msg->GetPInterface() == ObservTimer)
				{

					//Next transition is  TakeImage
					edroomCurrentTrans.localId = TakeImage;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



