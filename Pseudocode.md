REVISED PSEUDOCODE

int ferrisWheelSpeed
int minimumFerrisWheelSpeed

int staircaseSpeed
int minimumStaircaseSpeed

setup:
  import Arduino libraries
  import other libraries
  initialise pins

loop:
  DetectRemote() // Ben and Quoc
  FerrisWheelMotor() // Irvin and Thomas
  StaircaseMotor() // Irvin and Thomas

DetectRemote: // Ben and Quoc
  if(remotePressed):
    DisplayGroupBoxPattern() // Rumeth, Vikil and Eugene
  else:
    DisplayOurBoxPattern() // Rumeth, Vikil and Eugene

FerrisWheelMotor: // Irvin and Thomas
  run ferrisWheelMotor
  ferrisWheelSpeed = motorSpeed

StaircaseMotor: // Irvin and Thomas
  run staircaseMotor
  staircaseSpeed = motorSpeed

DisplayOurBoxPattern: // Rumeth, Vikil and Eugene
  if(ferrisWheelSpeed < minimumFerrisWheelSpeed):
    display red lights on ferris wheel
  else:
    display repeating interesting patterns
  if(staircaseSpeed < minimumStaircaseSpeed):
    display red lights on staircase
  else:
    display repeating interesting patterns

DisplayGroupBoxPattern: // Rumeth, Vikil and Eugene
  if(ferrisWheelSpeed < minimumFerrisWheelSpeed):
    display red lights on ferris wheel
  else:
    display group box pattern on ferris wheel
  if(staircaseSpeed < minimumStaircaseSpeed):
    display red lights on staircase
  else:
    display group box pattern on staircase
