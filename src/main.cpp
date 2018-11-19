#include <ReefAngel_Features.h>
#include <ReefAngel.h>
#include <ReefAngelStar.h>
#include <RA_TouchMenu.h>

////// Place global variable code below here
ReefAngelStarClass myRA = ReefAngelStarClass();
ReefAngelClass *ReefAngel = &myRA;

////// Place global variable code above here


void setup()
{
    // This must be the first line
    ReefAngel->Init();  //Initialize controller
    TouchMenu.Init();
    ReefAngel->Star();
    // Ports toggled in Feeding Mode
    ReefAngel->FeedingModePorts = 0;
    ReefAngel->FeedingModePortsE[0] = Port1Bit | Port3Bit | Port4Bit;
    ReefAngel->FeedingModePortsE[1] = 0;
    // Ports toggled in Water Change Mode
    ReefAngel->WaterChangePorts = 0;
    ReefAngel->WaterChangePortsE[0] = Port1Bit | Port3Bit | Port4Bit;
    ReefAngel->WaterChangePortsE[1] = 0;
    // Ports turned off when Overheat temperature exceeded
    ReefAngel->OverheatShutoffPorts = 0;
    ReefAngel->OverheatShutoffPortsE[0] = Port3Bit | Port4Bit;
    ReefAngel->OverheatShutoffPortsE[1] = 0;
    // Ports turned off when Leak is detected
    ReefAngel->LeakShutoffPorts = 0;
    ReefAngel->LeakShutoffPortsE[0] = Port1Bit | Port3Bit | Port4Bit | Port5Bit;
    ReefAngel->LeakShutoffPortsE[1] = 0;
    // Ports toggled when Lights On / Off menu entry selected
    ReefAngel->LightsOnPorts = 0;
    ReefAngel->LightsOnPortsE[0] = Port2Bit;
    ReefAngel->LightsOnPortsE[1] = 0;
    // Use T1 probe as temperature and overheat functions
    ReefAngel->TempProbe = T1_PROBE;
    ReefAngel->OverheatProbe = T1_PROBE;
    // Set the Overheat temperature setting
    InternalMemory.OverheatTemp_write( 780 );

    // Ports that are always on
    ReefAngel->Relay.On( Box1_Port3 );
    ReefAngel->Relay.On( Box1_Port4 );
    ReefAngel->Relay.On( Box1_Port6 );
    ReefAngel->Relay.On( Box1_Port7 );
    ReefAngel->Relay.On( Box1_Port8 );

    ////// Place additional initialization code below here


    ////// Place additional initialization code above here
}

void loop()
{
    ReefAngel->StandardLights( Box1_Port1,11,45,20,15 );
    ReefAngel->StandardLights( Box1_Port2,12,45,21,0 );
    ReefAngel->StandardHeater( T1_PROBE,Box1_Port5,745,750 );
    ReefAngel->PWM.SetDaylight( PWMSlope( 9,0,17,0,15,70,60,0 ) );

    boolean buzzer=false;
    if ( ReefAngel->isATOTimeOut() ) buzzer=true;
    if ( ReefAngel->isOverheat() ) buzzer=true;
    if ( ReefAngel->isBusLock() ) buzzer=true;
    if ( buzzer ) ReefAngel->BuzzerOn(2); else ReefAngel->BuzzerOff();

    ////// Place your custom code below here


    ////// Place your custom code above here

    ReefAngel->Network.Cloud();
    // This should always be the last line
    TouchMenu.ShowTouchInterface();
}
