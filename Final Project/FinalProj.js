var inAttendance = [0, 0, 0, 0, 0];

misty.ChangeLED(255, 255, 255);

misty.StartFaceRecognition();

function registerFaceRec() {
    misty.AddPropertyTest("FaceRec", "Label", "exists", "", "string");
    misty.RegisterEvent("FaceRec", "FaceRecognition", 1000, true);
}


function waveRightArm() {
    misty.MoveArmDegrees("right", -80, 30); // Right arm up to wave
    misty.Pause(3000); // Pause with arm up for 3 seconds
    misty.MoveArmDegrees("both", 80, 30); // Both arms down
}

function waveLeftArm() {
    misty.MoveArmDegrees("left", -80, 30); // Right arm up to wave
    misty.Pause(3000); // Pause with arm up for 3 seconds
    misty.MoveArmDegrees("both", 80, 30); // Both arms down
}

function _FaceRec(data){
    var faceDetected = data.PropertyTestResults[0].PropertyValue;
    
    if(faceDetected == "unknown person"){
        //maybe something that says that this is not a person in the class
        misty.ChangeLED(255, 255, 0); //flash yellow
        misty.pause(1000) //pause 5 seconds
        misty.ChangeLED(255, 255, 255); //change back to white
    }

    else if (faceDetected == "Bernadette") {
        if (inAttendance[0] == 0) {
            misty.PlayAudio("Bernadette-welcome.mp3", 100);
            waveRightArm();
            inAttendance[0] = 1;
            misty.ChangeLED(0, 255, 0); //flash green
            misty.pause(1000) //pause 5 seconds
            misty.ChangeLED(255, 255, 255); //change back to white
        }
        else {
            misty.ChangeLED(0, 0, 255); //flash blue if the person is already in attendance
            misty.pause(1000) //pause 5 seconds
            misty.ChangeLED(255, 255, 255); //change back to white
        }
        
    }

    else if (faceDetected == "CJ") {
        if (inAttendance[1] == 0) {
            misty.PlayAudio("CJ-welcome.mp3", 100);
            waveRightArm();
            inAttendance[1] = 1;
            misty.ChangeLED(0, 255, 0); //flash green
            misty.pause(1000) //pause 5 seconds
            misty.ChangeLED(255, 255, 255); //change back to white
        }
        else {
            misty.ChangeLED(0, 0, 255); //flash blue if the person is already in attendance
            misty.pause(1000) //pause 5 seconds
            misty.ChangeLED(255, 255, 255); //change back to white
        }
        
    }

    else if (faceDetected == "Skyeler") {
        if (inAttendance[2] == 0) {
            misty.PlayAudio("Skyeler-welcome.mp3", 100);
            waveRightArm();
            inAttendance[2] = 1;
            misty.ChangeLED(0, 255, 0); //flash green
            misty.pause(1000) //pause 5 seconds
            misty.ChangeLED(255, 255, 255); //change back to white
        }
        else {
            misty.ChangeLED(0, 0, 255); //flash blue if the person is already in attendance
            misty.pause(1000) //pause 5 seconds
            misty.ChangeLED(255, 255, 255); //change back to white
        }
        
        
    }

    else if (faceDetected == "Nick"){
        if (inAttendance[3] == 0) {
            misty.ChangeLED(0, 255, 0); //flash green
            misty.PlayAudio("Nick-welcome.mp3", 100);
            waveRightArm();
            inAttendance[3] = 1;
            misty.pause(1000) //pause 5 seconds
            misty.ChangeLED(255, 255, 255); //change back to white
        }
        else {
            misty.ChangeLED(0, 0, 255); //flash blue if the person is already in attendance
            misty.pause(1000) //pause 5 seconds
            misty.ChangeLED(255, 255, 255); //change back to white
        }
        
    }

    else if (faceDetected == "Bangyao") {
        if (inAttendance[4] == 0) {
            misty.PlayAudio("Bangyao-welcome.mp3", 100);
            waveRightArm();
            inAttendance[4] = 1;
            misty.ChangeLED(0, 255, 0); //flash green
            misty.pause(1000) //pause 5 seconds
            misty.ChangeLED(255, 255, 255); //change back to white
        }
        else {
            misty.ChangeLED(0, 0, 255); //flash blue if the person is already in attendance
            misty.pause(1000) //pause 5 seconds
            misty.ChangeLED(255, 255, 255); //change back to white
        }
       
    }

    else if (faceDetected == "Blythe" || faceDetected == "Jeevanjee") {
        waveRightArm();
        misty.ChangeLED(255, 0, 255); //change light to purple
        var count = 0;
        for (var i = 0; i < 5; i++) {
            if (inAttendance[i] == 1){
                count ++;
            }
        }
        if(count == 0) {
            //"There are 0 students in the class room"
            misty.PlayAudio("0-peoplePresent.mp3", 100);
        }
        else if(count == 1) {
            misty.PlayAudio("1-peoplePresent.mp3", 100);
        }
        else if(count == 2) {
            misty.PlayAudio("2-peoplePresent.mp3", 100);
        }
        else if(count == 3) {
            misty.PlayAudio("3-peoplePresent.mpy3", 100);
        }
        else if(count == 4) {
            misty.PlayAudio("4-peoplePresent.mp3", 100);
        }
        else if(count == 5) {
            misty.PlayAudio("5-PeoplePresent.mp3", 100);
        }
        else {
            waveLeftArm();
        }
        misty.ChangeLED(255, 255, 255); //change back to white
     }
}

registerFaceRec();

//misty.Pause(100000);
