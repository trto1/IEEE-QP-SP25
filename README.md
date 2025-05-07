# IEEE-QP-SP25
## Tamagotchi
Here are some functions we need / how the overall code structure might work:

`setup () {
    setup the pet and bars interface;
    updateHungerAfter();
    updateHappiness();
}`

This is where we do live stuff while the machine is on, including:
- handle pushed buttons
- feeding the pet with meals and snacks
  - update screen as needed
- idle animation for the pet
- (optional) happiness-related games
  
`loop () {
        handleInputs();
        updateHungerLive();
        some sort of delay?
}`
