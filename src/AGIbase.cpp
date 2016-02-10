#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int AGImain(){
	int i;
	Track currentTrack[INSTRUMENT_TYPES];
	Song currentSong = generateRandomSong(0,127);
	Song comparisonSong = generateRandomSong(1,127);
	for(i=0 i<INSTRUMENT_TYPES; i++){
		currentTrack[i] = decoupleTrack(currentSong, comparisonSong, i);
		findNoteCouple();
	}
}

Song generateRandomSong(int ID, int volume){
	Song newSong;
	int BPM = MIN_TEMPO+(MAX_TEMPO-MIN_TEMP)*rand();
	int maxInstruments = 49*rand(), i;
	newSong.song_id = ID;
	for(i=0; i<maxInstruments; i++)
		newSong.tunes[i] = generateRandomTrack(i, volume);
	newSong.tunes[maxInstrument] = '\0';
	return newSong;

}

Track generateRandomTrack(int ID, int volume){
	Track newTrack;
	Note newNote;
	int i = 0, j = 0;
	newTrack.instrument_id = INSTRUMENT_NUMBER*(ID+rand())/INSTRUMENT_TYPES%INSTRUMENT_NUMBER;
	while(j<MAX_NOTES){
		newNote.pause_time = 16*rand(); 
		newNote.hold_time = 16*rand(); 
		if((j+newNote.hold_time)>MAX_NOTES){
			newNote.hold_time = MAX_NOTES-j;
			newNote.pause_time = 0;
		}
		if((j+newNote.hold_time+newNote.pause_time)>MAX_NOTES){
			newNote.pause_time = MAX_NOTES-newNote.hold_time-j;
		}
		newNote.tone = TONE_NUMBER * rand();
		newTrack.channel[i++] = newNote;
		newTrack.volume = volume;
		j += newNote.pause_time + newNote.hold_time;
	}
	newTrack.channel[i] = '\0';
}

Track decoupleTrack(Song importantSong, Song testSong, int instrumentIndex){
	int score[6], i, song_id;
	Song tempSongs[5]; 
	tempSong[0].tunes[0] = importantSong[instrumentIndex];
	tempSong[0].tunes[1] = testSong[instrumentIndex];

	tempSong[1].tunes[0] = importantSong[instrumentIndex];
	tempSong[1] = trackSkipper(testSong, instrumentIndex, 1);


	tempSong[2].tunes[0] = testSong[instrumentIndex];
	tempSong[2] = trackSkipper(importantSong, instrumentIndex, 1);	

	tempSong[3] = trackSkipper(importantSong, instrumentIndex, 1);

	song_id = tempSong[3].song_id-1;
	
	tempSong[4] = trackSkipper(importantSong, instrumentIndex, song_id);

	for(i = 0; i<tempSong; i++){
		tempSong[3].tunes[song_id+i] = tempSong[4].tunes[song_id+i];
	}
		
	//submit the following songs to the critic;
	score[0] = critic(importantSong);
	score[1] = critic(testSong);
	score[2] = critic(tempSong[0]);
	score[3] = critic(tempSong[1]);
	score[4] = critic(tempSong[2]);
	score[5] = critic(tempSong[3]);
		
}

Song trackSkipper(Song insertSong, int skipID, int startAddIndex){
	int i;
	Song tempSong;
	for(i=0; i<skipID; i++){
		tempSong.tunes[i+startInsertIndex] = insertSong.tunes[i];
	}
	while(testSong.tunes[i+startIndex] != '\0'){
		tempSong.tunes[i+startInsertIndex] = insertSong.tunes[i+1];
		i++;
	}
	tempSong.tunes[i] = '\0';
	tempSong.song_id = i;
	return tempSong;
}

void findNotePair(){
	
}
