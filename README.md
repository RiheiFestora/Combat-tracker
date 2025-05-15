------------------
The Combat Tracker
------------------
This application is my implementation of a combat tracker, which registers participants in a turn based
combat, similar to how Dungeons and Dragons combat works. Participants can be added with "add participants" button,
which adds a blank participant to the combat list, or through the file menu "load participants", 
which can be used to load up a list of premade participants. From the same menu, the current participants can also be
stored in a JSON file.
The list can be sorted with "sort participants" button, which will sort them in descending order based on the integer
value after their name field. This is the same logic which is used in Dungeons and Dragons.
"Start combat" button adds a mark to the first participant, indicating that it is their turn, this will also start
a stopwatch attached to them, which will keep track how much time the participant has taken in the current combat.
The button also adds two new buttons, "previous participant" and "next participant" which can be used to cycle through the
participants in the list, incrementing or decrementing the current round when the list is cycled through.


---------------
The Source code
---------------
To launch the source code, you will need Qt 6.9.0 (I haven't tested other versions).
I used visual studio to create this and the vcxproj file is provided alongside the source code.

---------------
The Application
---------------
1. Download the latest release .zip
2. Extract the zip file wherever you want on your own computer
3. Launch the Combat_tracker.exe file in the extracted folder
4. Enjoy the combat tracker!
