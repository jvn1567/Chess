# Chess
This program runs a chess game against an AI.

![ezgif com-gif-maker (3)](https://user-images.githubusercontent.com/56368354/126096531-011c6e6a-cc76-4689-bed3-32f5c53df23c.gif)

# Player Help Features
The player clicks on the piece they wish to move, will generate colored guides.
  -The selected piece will be displayed with an orange tile border.
  -Movable tiles will be displayed with a yellow tile border.
  -Movable tiles containing enemy pieces will be displayed with a red tile border.
  -If your king is currently being checked, the tile under it will be completely red.
  
# AI
The AI will control black pieces, and choose its moves by using a minimax algorithm. All moves up to a specified depth are explored and the board state values are stored in a tree. The minimum value of a branch will be passed up when optimizing for black side's turn, and the maximum for white's turn. The AI will then add all moves with the best final path to a vector to choose randomly from.

For example, take a depth of 2 and the move values {{5, 5, 5}, {2, 5, 2}, {3, 7, 3}}. This corresponds to simulating one black turn and one white turn. On the bottom branches, the program will optimize to maximize the board values, which would be assuming that the player makes the best possible move for themselves. These maximums are passed up the tree to obtain {5, 5, 7}. Now the program optimizes for black side, and will select the mimimum. Therefore, the first and second moves in the tree are most optimal and the AI will select from one of the two to make.

The GUI is built using Simple Graphics Library (SGL) by Marty Stepp, which can be found at https://github.com/stepp/sgl

