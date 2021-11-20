# Chess
This program runs a chess game against an AI.

![ezgif com-gif-maker (9)](https://user-images.githubusercontent.com/56368354/142670646-611e3c6d-c7dc-4adc-bca2-c4248feab302.gif)

# Player Help Features
Simple colored indicators and elements appear to help display moves and game state to the player.
  - The selected piece will be displayed with an orange tile border.
  - Movable tiles will be displayed with a yellow tile border.
  - Movable tiles containing enemy pieces will be displayed with a red tile border.
  - If the player's king is currently being checked, the tile under it will be completely red.
  - Captured pieces for both sides are displayed separated and in order of piece value.
  
# AI
The AI will control black pieces, and choose its moves by using a minimax algorithm. Moves up to a specified depth (default 3) are explored, and board states are scored on the total value of all pieces currently present. Alpha-beta pruning is implemented to reduce the number of moves that must be calculated by keeping track of the best possible board scores for both players.

# Future Work
Some noticeable issues occur when the AI's possible moves all result in the same score, causing the AI to occasionally just move back and forth until the player's pieces approach closer. This is due to the current algorithm selecting the first out of all tied moves, since pruned branches may end up tied in score with the actual optimal move. This can be mitigated by implementing a positional map, with values for each board location. Values from this map would be added to the board score to force pieces to favor moving towards certain positions on the board and help break tied scores.

The current algorithm also struggles to finish off the player, as it has no sense of how to checkmate the player's king. This was partially mitigated by inflating the value of the king piece, and could possibly be improved further by having the AI favor moves that result in capturing enemy pieces. However, this may have a side effect of making the AI recklessly sacrifice its pieces.

# Libraries
The GUI is built using Simple Graphics Library (SGL) by Marty Stepp, which can be found [here](https://github.com/stepp/sgl).
