# Zorkish
A partial remake of the classic Zork. 

## Features
- Fully-featured XML world loader that is capable of specifying room location, contents and description, the player’s location as well as the items and health they start with, trap location and damage, items that contain items, etc. As a result, the game contains absolutely zero world specification; instead the player is able to select which level to play based on what is found in the /worlds/ directory.
- Messaging, Announcements and Blackboards framework: A versatile and very easy to manage messaging system. So far only used by traps to determine when to trigger based on PlayerMovedMessages.
