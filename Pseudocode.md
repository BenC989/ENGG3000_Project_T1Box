PSEUDOCODE

setup:  
  import Arduino libraries
  import other libraries
  initialise pins

loop:
  DetectRemote() // Ben and Quoc
  RunFerrisWheel() // Irvin (lights), Rumeth (motor)
  RunStaircase() // Vikil (lights), Thomas (motor)
  RunTrackSplitter() // Eugene 
  
DetectRemote:
  if(RemotePressed):
    do groupBoxPatternFerrisWheel
    do groupBoxPatternStaircase
  else:
    do singleBoxPatternFerrisWheel
    do singleBoxPatternStaircase

RunFerrisWheel:
  try {
    run ferrisWheelMotor
    make pattern green
  }
  catch (IOexception e){
    make pattern red
  }

RunStairCase:  
  try {
    run staircaseMotor
    make pattern green
  }
  catch (IOexception e){
    make pattern red
  }

RunTrackSplitter:
  sumMarbles = 0
  if(enterSensorTriggered): 
    sumMarbles++
    if(sumMarbles == 4):
      closeRightSide // direct marbles to the staircase (left side)
      setTrafficLight to red
    else: 
      openRightSide
      setTrafficLight to green
  if(exitSensorTriggered):
      sumMarbles--
