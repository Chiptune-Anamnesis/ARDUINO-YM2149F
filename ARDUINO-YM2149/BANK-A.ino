void playNote(byte note, byte velo, byte chan, int pitchBendValue) {
    chan = chan + 1;
    if (note < 24) return; // Invalid note, exit function
    setPinHigh(__LEDPORT__, __LED__);

// MIDI Channel 1
    if (chan == 1) {
    noteActiveA = 1;
    detuneActiveA = 1;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;     
    noteA = note;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    int periodA = (tp[note]  + detuneValue) * pitchBendFactor;
    byte LSB = (periodA & 0xFF);
    byte MSB = ((periodA >> 8) & 0x0F);
    cli();
    setMixer(true, false, false, false, false, false);
    send_data(0x00, LSB);
    send_data(0x01, MSB);
    setVolume(0, defaultVolume, -2);
    (controlValue11 == 0) ? setEnvelope(0xF000, 0x1000) : updateEnvelope();
    sei();
    }
// MIDI Channel 2
    else if (chan == 2) {
    noteActiveB = 1;
    detuneActiveB = 1;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;    
    noteB = note;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    int periodB = (tp[note]   + detuneValue) * pitchBendFactor;
    byte LSB = (periodB & 0xFF);
    byte MSB = ((periodB >> 8) & 0x0F);
    cli();
    setMixer(false, false, true, false, false, false);
    send_data(0x02, LSB);
    send_data(0x03, MSB);
    setVolume(1, defaultVolume, -2);
   (controlValue11 == 0) ? setEnvelope(0xF000, 0x1000) : updateEnvelope();
    sei();
    }
// MIDI Channel 3
    else if (chan == 3) {
      noteActiveC = 1;
    detuneActiveC = 1;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;      
    noteC = note;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    int periodC = (tp[note]   + detuneValue) * pitchBendFactor;
    byte LSB = (periodC & 0xFF);
    byte MSB = ((periodC >> 8) & 0x0F);
    cli();
    setMixer(false, false, false, false, true, false);
    send_data(0x04, LSB);
    send_data(0x05, MSB);
    setVolume(2, defaultVolume, -2);
    (controlValue11 == 0) ? setEnvelope(0xF000, 0x1000) : updateEnvelope();
    sei();
    }
// MIDI Channel 4
    else if (chan == 4) {
            noteActiveA = 1;
            noteActiveB = 1;
            detuneActiveB = 1;
            arpeggioFlipMe = true;
            timerTicks = 0;
            arpeggioCounter = 0;          
            noteA = note;
            noteB = note;
            float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
            int periodA = tp[note] * pitchBendFactor;
            periodB = (tp[note] + (detuneValue + 1)) * pitchBendFactor;
            byte ALSB = (periodA & 0x00FF);
            byte AMSB = ((periodA >> 8) & 0x000F);
            byte BLSB = (periodB & 0x00FF);
            byte BMSB = ((periodB >> 8) & 0x000F);
            cli();
            setMixer(true, false, true, false, true, false);
            send_data(0x00, ALSB);
            send_data(0x01, AMSB);
            send_data(0x02, BLSB);
            send_data(0x03, BMSB);
            setVolume(0, defaultVolume, 0);
            setVolume(1, defaultVolume, 0);
            setVolume(2, defaultVolume, 0);
            (controlValue11 == 0) ? setEnvelope(0xF000, 0x1000) : updateEnvelope();
            sei();
    }
// MIDI Channel 5
else if (chan == 5) { 
     noteActiveA = 1;
    noteActiveB = 1;
    noteActiveC = 1;
    detuneActiveC = 1;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;  
    noteA = note;
    noteB = note;
    noteC = note;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    int periodA = (tp[note] - 12) * pitchBendFactor;
    int periodB = (tp[note]) * pitchBendFactor;
    int periodC = (tp[note] + (detuneValue + 1)) * pitchBendFactor;
    byte ALSB = (periodA & 0x00FF);
    byte AMSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    byte CLSB = (periodC & 0x00FF);
    byte CMSB = ((periodC >> 8) & 0x000F);
    cli();
    setMixer(true, false, true, false, true, false);
    send_data(0x00, ALSB);
    send_data(0x01, AMSB);
    send_data(0x02, BLSB);
    send_data(0x03, BMSB);
    send_data(0x04, CLSB);
    send_data(0x05, CMSB);
    setVolume(0, defaultVolume, 0);
    setVolume(1, defaultVolume, 0);
    setVolume(2, defaultVolume, 0);
    (controlValue11 == 0) ? setEnvelope(0xF000, 0x1000) : updateEnvelope();
    sei();
}
// MIDI Channel 6
else if (chan == 6) { 
    noteActiveA = 1;
    noteActiveB = 1;
    detuneActiveA = 0;
    noteA = note;
    noteB = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    float detuneFactorA = 1.006;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = (envTp00[note -12]  + detuneValue) * pitchBendFactor * detuneFactorA;
    periodB = (envTp02[note]  + detuneValue) * pitchBendFactor;
    byte LSB = (periodA & 0x00FF);
    byte MSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    cli();
    setMixer(true, false, true, false, false, false);
    send_data(0x00, LSB);
    send_data(0x01, MSB);
    send_data(0x02, LSB);
    send_data(0x03, MSB);
    //send_data(0x0B, BLSB);
    //send_data(0x0C, BMSB);
    setVolume(0, defaultVolume, 0);
    setVolume(1, defaultVolume, -1);
    (controlValue11 == 0) ? setEnvelope(0xF000, 0x0B) : updateEnvelope();
    sei();
}
// MIDI Channel 7
else if (chan == 7) { 
    noteActiveA = 1;
    detuneActiveA = 0;
    noteA = note;
    noteB = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = (tp[note -24]) * pitchBendFactor;
    periodB = (envTp00[note -12] + detuneValue) * pitchBendFactor;
    byte LSB = (periodA & 0x00FF);
    byte MSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    cli();
    setMixer(true, false, true, false, false, false);
    send_data(0x00, LSB);
    send_data(0x01, MSB);
    send_data(0x02, BLSB);
    send_data(0x03, BMSB);
    send_data(0x0B, LSB);
    send_data(0x0C, MSB);
    setVolume(0, defaultVolume, 0);
    setVolume(1, defaultVolume, 0);
    (controlValue11 == 0) ? setEnvelope(0xF000, 0x08) : updateEnvelope();
    sei();
}
// MIDI Channel 8
else if (chan == 8) { 
    noteActiveA = 1;
    noteActiveB = 1;
    detuneActiveC = 1;
    noteA = note;
    noteB = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = envTp00[note]  * pitchBendFactor;
    periodB = ((tp[note - 12] + detuneValue) << 1)* pitchBendFactor;
    byte LSB = (periodA & 0x00FF);
    byte MSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    cli();
    setMixer(true, false, true, false, false, false);
    send_data(0x02, BLSB);
    send_data(0x03, BMSB);
    send_data(0x0B, LSB);
    send_data(0x0C, MSB);
    setVolume(0, defaultVolume, 0);
    setVolume(1, defaultVolume, 0);
    (controlValue11 == 0) ? setEnvelope(0xF000, 0x02) : updateEnvelope();
    sei();
}
// MIDI Channel 9
else if (chan == 9) {
    noteActiveA = 1;
    noteActiveB = 1;
    detuneActiveB = 1;
    noteA = note;
    noteB = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = envTp01[note -24] * pitchBendFactor;
    periodB = (tp[note - 12]  + detuneValue) * pitchBendFactor;
    byte LSB = (periodA & 0x00FF);
    byte MSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    cli();
    setMixer(true, false, true, false, false, false); 
    send_data(0x00, LSB);
    send_data(0x01, MSB);
    send_data(0x02, BLSB);
    send_data(0x03, BMSB);
    send_data(0x0B, LSB);
    send_data(0x0C, MSB);
    setVolume(0, defaultVolume, 0);
    setVolume(1, defaultVolume, 0);
    (controlValue11 == 0) ? setEnvelope(0xF000, 0x09) : updateEnvelope();
    sei();
}
// MIDI Channel 11
else if (chan == 11) {
    noteActiveA = 1;
    noteActiveC = 1;
    detuneActiveA = 0;
    noteA = note;
    noteC = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = (envTp00[note]   + detuneValue) * pitchBendFactor;
    periodC = tp[note -12] * pitchBendFactor;
    byte LSB = (periodA & 0x00FF);
    byte MSB = ((periodA >> 8) & 0x000F);
    byte CLSB = (periodC & 0x00FF);
    byte CMSB = ((periodC >> 8) & 0x000F);
    cli();
    setMixer(true, false, false, false, true, false);
    send_data(0x00, LSB);
    send_data(0x01, MSB);
    send_data(0x04, CLSB);
    send_data(0x05, CMSB);
    setVolume(0, defaultVolume, 0);
    setVolume(2, defaultVolume, -3);
    (controlValue11 == 0) ? setEnvelope(0x0001, 0x0D) : updateEnvelope();
    sei();
}
// MIDI Channel 12
else if (chan == 12) 
{
    noteActiveA = 1;
    noteActiveB = 1;
    noteActiveC = 1;
    detuneActiveC = 0;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    noteA = note;
    noteB = note;
    noteC = note;
    float detuneFactor = 1.10;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = (tp[note - 12]  + detuneValue)  * pitchBendFactor;
    periodB = tp[note + 12] * pitchBendFactor * detuneFactor;
    periodC = tp[note] * pitchBendFactor;  
    byte ALSB = (periodA & 0x00FF);
    byte AMSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    byte CLSB = (periodC & 0x00FF);
    byte CMSB = ((periodC >> 8) & 0x000F);
    cli();
    setMixer(true, false, true, false, true, false);
    send_data(0x08, 0x10);
    send_data(0x0B, BLSB);
    send_data(0x0C, BMSB);
    send_data(0x00, ALSB);
    send_data(0x01, AMSB);
    send_data(0x04, CLSB);
    send_data(0x05, CMSB);
    setVolume(0, defaultVolume, -2);
    setVolume(1, defaultVolume, 0);
    setVolume(2, defaultVolume, 0);
    (controlValue11 == 0) ? setEnvelope(0xF000, 0x00) : updateEnvelope();
    sei();
}
// MIDI Channel 13
else if (chan == 13)
{
    noteActiveA = 1;
    noteActiveB = 1;
    noteActiveC = 1;
    detuneActiveC = 0;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    noteA = note;
    noteB = note;
    noteC = note;
    float detuneFactorA = 1.017;
    float detuneFactorB = 1.01;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = (tp[note - 12]  + detuneValue) * pitchBendFactor;
    periodB = tp[note - 12] * pitchBendFactor * detuneFactorA;
    periodC = tp[note] * pitchBendFactor * detuneFactorB;
    byte ALSB = (periodA & 0x00FF);
    byte AMSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    byte CLSB = (periodC & 0x00FF);
    byte CMSB = ((periodC >> 8) & 0x000F);
    cli();
    setMixer(true, false, true, false, true, false);
    send_data(0x0B, BLSB);
    send_data(0x0C, BMSB);
    send_data(0x00, ALSB);
    send_data(0x01, AMSB);
    send_data(0x04, CLSB);
    send_data(0x05, CMSB);
    setVolume(0, defaultVolume, 0);
    setVolume(1, defaultVolume, 0);
    setVolume(2, defaultVolume, 0);
    (controlValue11 == 0) ? setEnvelope(0xF000, 0x02) : updateEnvelope();
    sei();
}
// MIDI Channel 14
else if (chan == 14)
{
    noteActiveA = 1;
    noteActiveB = 1;
    noteActiveC = 1;
    detuneActiveC = 1;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    noteA = note;
    noteB = note;
    noteC = note;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    int periodA = (tp[note]) * pitchBendFactor;
    int periodB = (tp[note]) * pitchBendFactor;
    int periodC = (tp[note] + detuneValue) * pitchBendFactor;
    
    byte ALSB = (periodA & 0x00FF);
    byte AMSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    byte CLSB = (periodC & 0x00FF);
    byte CMSB = ((periodC >> 8) & 0x000F);

    cli();
    setMixer(true, false, true, false, true, false);
    send_data(0x00, ALSB);
    send_data(0x01, AMSB);
    send_data(0x02, BLSB);
    send_data(0x03, BMSB);
    send_data(0x04, CLSB);
    send_data(0x05, CMSB);
    setVolume(0, defaultVolume, 0);
    setVolume(1, defaultVolume, 0);
    setVolume(2, defaultVolume, 0);
    (controlValue11 == 0) ? setEnvelope(0xF000, 0x02) : updateEnvelope();
    sei();
}
}

/**
 * @brief Stops a MIDI note for a specified channel.
 *
 * This function resets the note and period for the specified MIDI channel
 * and sends commands to stop the sound associated with that note.
 *
 * @param note The MIDI note number to stop.
 * @param chan The MIDI channel number corresponding to the note.
 */
void stopNote(byte note, byte chan)
{
chan = chan + 1;
// MIDI Channel 1
    if (chan == 1 && note == noteA) {
        noteActiveA = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        setVolume(0, 0, 0); 
        setEnvelope(0x0000, 0x00);
        sei();
    }
// MIDI Channel 2
    else if (chan == 2 && note == noteB) {
        noteActiveB = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteB = periodB = 0;
        cli();
        send_data(0x02, 0);
        send_data(0x03, 0);
        setVolume(1, 0, 0); 
        setEnvelope(0x0000, 0x00);
        sei();
    }
// MIDI Channel 3
    else if (chan == 3 && note == noteC) {
        noteActiveC = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteC = periodC = 0;
        cli();
        send_data(0x04, 0);
        send_data(0x05, 0); 
        setVolume(2, 0, 0); 
        setEnvelope(0x0000, 0x00);
        sei();
    }
// MIDI Channel 4
    else if (chan == 4 && note == noteA) {
        noteActiveA = 0;
        noteActiveB = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        setEnvelope(0x0000, 0x00);
        setVolume(0, 0, 0);
        setVolume(1, 0, 0);
        sei();
    }
// MIDI Channel 5
    else if (chan == 5 && note == noteA) {
        timerTicks = 0;
        noteActiveA = 0;
        noteActiveB = 0;
        noteActiveC = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        noteC = periodC = 0;
        arpeggioFlipMe = false;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        send_data(0x04, 0);
        send_data(0x05, 0);
        setEnvelope(0x0000, 0x00);
        setVolume(0, 0, 0);
        setVolume(1, 0, 0);
        setVolume(2, 0, 0);
        sei();
    }
// MIDI Channel 6
    else if (chan == 6 && note == noteA) {
        noteActiveA = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        setEnvelope(0x0000, 0x00);
        setVolume(0, 0, 0);
        setVolume(1, 0, 0);
        sei();
    }
// MIDI Channel 7
    else if (chan == 7 && note == noteA) {
        noteActiveA = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        setEnvelope(0x0000, 0x00);
        setVolume(0, 0, 0);
        setVolume(1, 0, 0);
        sei();
    }
// MIDI Channel 8
    else if (chan == 8 && note == noteA) {
        noteActiveA = 0;
        noteActiveB = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        send_data(0x0B, 0);
        send_data(0x0C, 0);
        setEnvelope(0x0000, 0x00);
        setVolume(0, 0, 0);
        setVolume(1, 0, 0);
        sei();
    }
// MIDI Channel 9
    else if (chan == 9 && note == noteA) {
        noteActiveA = 0;
        noteActiveB = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        send_data(0x0B, 0);
        send_data(0x0C, 0);
        setEnvelope(0x0000, 0x00);
        setVolume(0, 0, 0);
        setVolume(1, 0, 0);
        sei();
    }
// MIDI Channel 11
    else if (chan == 11 && note == noteA) {
        timerTicks = 0;
        noteActiveA = 0;
        noteActiveC = 0;
        noteA = periodA = 0;
        noteC = periodC = 0;
        arpeggioFlipMe = false;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x04, 0);
        send_data(0x05, 0);
        setEnvelope(0x0000, 0x00);
        setVolume(0, 0, 0);
        setVolume(2, 0, 0);
        sei();
    }
// MIDI Channel 12
    else if (chan == 12 && note == noteA) {        
        noteActiveA = 0;
        noteActiveB = 0;
        noteActiveC = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        noteC = periodC = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0); 
        send_data(0x04, 0); 
        send_data(0x05, 0); 
        setEnvelope(0x0000, 0x00); 
        setVolume(0, 0, 0); 
        setVolume(1, 0, 0); 
        setVolume(2, 0, 0); 
        sei(); 
    }
// MIDI Channel 13
    else if (chan == 13 && note == noteA) {
        noteActiveA = 0;
        noteActiveB = 0;
        noteActiveC = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        noteC = periodC = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        send_data(0x04, 0); 
        send_data(0x05, 0); 
        setEnvelope(0x0000, 0x00); 
        setVolume(0, 0, 0); 
        setVolume(1, 0, 0); 
        setVolume(2, 0, 0); 
        sei(); 
    }
// MIDI Channel 14
    else if (chan == 14 && note == noteA) {
        noteActiveA = 0;
        noteActiveB = 0;
        noteActiveC = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        noteC = periodC = 0; 
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        send_data(0x04, 0);
        send_data(0x05, 0);
        setEnvelope(0x0000, 0x00); 
        setVolume(0, 0, 0); 
        setVolume(1, 0, 0); 
        setVolume(2, 0, 0); 
        sei();
    }
}
