#include "opcontrol.h"
#include "auton.h"


bool reverseDrive = false, hanging = false, hangDone = false;

MotorGroup leftMotors({
  Motor("fl", &fl),
  Motor("ml", &ml),
  Motor("bl", &bl)
});

MotorGroup rightMotors({
  Motor("fr", &fr),
  Motor("mr", &mr),
  Motor("br", &br)
});

MotorGroup intakeMtrs({
  Motor("intake1", &intake),
  Motor("intake2", &intake2)
});

ChassisGeometry chassisGeometry(&leftMotors, &rightMotors, 1);
ChassisDriverSettings chassisDriverSettings(&controller, 1, 0, 800, true);
Tank chassis(chassisGeometry, chassisDriverSettings);

// PistonGroup frontWings({
//   Piston("left", &frontLeftWing),
//   Piston("right", &frontRightWing)
// });

// PistonGroup backWings({
//   Piston("left", &backLeftWing),
//   Piston("right", &backRightWing)
// });


void temperature() {
    controller.Screen.clearScreen();
    controller.Screen.setCursor(1, 1);
  controller.Screen.print("fl: %d          ", (int) fl.temperature(vex::percent));
  controller.Screen.print("fr: %d", (int) ml.temperature(vex::percent));
    controller.Screen.setCursor(2, 1);
  controller.Screen.print("ml: %d          ", (int) bl.temperature(vex::percent));
  controller.Screen.print("mr: %d", (int) fr.temperature(vex::percent));
    controller.Screen.setCursor(3, 1);
  controller.Screen.print("bl: %d          ", (int) mr.temperature(vex::percent));
  controller.Screen.print("br: %d", (int) br.temperature(vex::percent));
}


// void hangPressed() {

//   if (!hang && !hangDone) hang = true;
//   else if (!hangDone) {
//     pto = true;
//     hanging = true;
//     chassis.spinTank(12, 12, true, false);
//     wait(400, vex::msec);
//     hang = false;
//     hangDone = true;
//   }
// }


// void reverseDrivePressed() {

//   reverseDrive = !reverseDrive;
//   controller.rumble(".");
// }

void opcontrol() {

  //kills autonomous tasks

    taskHandler(true);


  //catapult initialization

  //   MotorGroup cataMotors({
  //     Motor("cata", &catapult),
  //     Motor("cata2", &catapult2)
  //   });
  //   Cata cata(&cataMotors, &cataRotation);
  //   cata.setResetSetpoint(0);
  //   cata.setPower(0.78);
  //   cata.setShotCounterBounds(15, 40);

  // //hang initialization

  //   controller.ButtonY.pressed(hangPressed);

  // //temperature checker
    
  //   controller.ButtonUp.pressed(temperature);

  // //for macro

  //   //auton();

  //drivetrain initialization

    leftMotors.setStopping(true);
    rightMotors.setStopping(true);
    int A1, A3;
    while (1)
    {

      // track system time

      uint64_t timestamp = vex::timer::systemHighResolution();

    //drivetrain code

    //  if (!hanging) (!reverseDrive) ? chassis.controllerFeedbackSpin() : chassis.controllerFeedbackSpin(true);

     A1 = controller.Axis1.value();
     A3 = controller.Axis3.value();

     chassis.spinTank(A3 + A1, A3 - A1);

     (controller.ButtonR2.pressing()) ? stick.set(true) : stick.set(false);
     (controller.ButtonL2.pressing()) ? lift.set(true) : lift.set(false);
     (controller.ButtonDown.pressing()) ? pisstake.set(true) : pisstake.set(false);
     (controller.ButtonY.pressing()) ? mogo.set(true) : mogo.set(false);
     (controller.ButtonRight.pressing()) ? redirect.set(true) : redirect.set(false);

    //intake code

      if (controller.ButtonL1.pressing()) intakeMtrs.spin(12);
      else if (controller.ButtonR1.pressing()) intakeMtrs.spin(-12);
      else intakeMtrs.stop();

    wait((timestamp + 11000.0 - vex::timer::systemHighResolution()) / 1000.0, vex::msec);
    }
}