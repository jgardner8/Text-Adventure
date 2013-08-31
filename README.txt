Zorkish - based on Zork

Current State:
- I think that's all of stream 2 core (was there a file loading part?)

TODO:
- Use .get/buffer check (slides) for non-blocking game loop
- http://stackoverflow.com/questions/582331/is-there-a-way-to-instantiate-objects-from-a-string-holding-their-class-name
- There is some memory leaks. There are some in Room, but I think most stem from the Inventory class. Other aComponents are freed perfectly... but not inventories.
- Loading adventures from files.