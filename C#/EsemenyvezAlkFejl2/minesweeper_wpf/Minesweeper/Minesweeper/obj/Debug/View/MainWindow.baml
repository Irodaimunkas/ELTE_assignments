   M S B A M L   `   `   `  ����F  BMinesweeper, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null)clr-namespace:MinesweeperMinesweeper  5   	       Minesweeper.MainWindow   5   	   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   +localclr-namespace:Minesweeper     5   	     � Title$  Minesweeper��5   	   $	��800��6   $	��800��6*    � 
ResizeMode$ NoResize=�66   .��5	      �  � RowDefinitions 5
   
   �� 5      $
��Auto �6   �� 5      $��* �6   �� 5      $
��Auto �6   .+�5   
   o� $��0��6   .@�5      m� $��New Game��6   .@�5      m� $
��Easy��6    m� Command 6)   �� *NewGameEasyCommand+m� 5      $��Medium��6    6+   �� *NewGameMediumCommand+m� 5      $
��Hard��6    6)   �� *NewGameHardCommand+5      m� 5      $��	Load Game��6    6*   �� *LoadGameOpenCommand+m� 5      $��	Save Game��6    6*   �� *SaveGameOpenCommand+5      �� 5   
   $��1��6   ��6$   �� *Fields+��5      �� 5      .R�5      A�  A� Rows 6"   �� *	MapSize+ A� Columns 6;   �� *	MapSize+5      ��5      �� 5      .R�5       �� $��24(�67   $
��Bold"�6E   ��6   �� *Value+��6W   �� *Color+ J� InputBindings 5!      d� 5"       d� Gesture$ 	LeftClicka�6+    �� Command 6?   �� *StepCommand+	 �� CommandParameter	 6_   �� *Number+d� 5#      $ 
RightClicka�6+    6@   �� *AlertCommand+	 6a   �� *Number+5%      5&      ��5(      �� 5)      .�5*      �� 
 �� Property
 � �� �� Value 61   �� *X+�� 5+      
 � �� 64   �� *Y+5,      5.      �� 5/   
   $��2��6   .@�50      �� .��51      �� $��Current Player: ��6   52      �� 53      .��54      �� ��6   �� *Player+55      56      57      58      