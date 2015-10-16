#LED-Matrix 5x11

LED-Matrix 5x11 is a driver tailored to fit the purposes of
a custom-build 5x11 LED-Matrix. The Matrix is multiplexed via
two HC595-Shift registers.

Text is displayed pictured in the following sheme:

## Initial Situation
![initial situation](Images/initial_situation.png)


## Calculate the width of the letter to insert
![calculate letter width](Images/calculate_letter_width.png)

## Empty the space for the next letter

![shift by one](Images/shift_1.png)

![shift by two](Images/shift_2.png)

![shift by three](Images/shift_3.png)

## Insert the new letter:
![insert new letter](Images/insert_new_letter.png)