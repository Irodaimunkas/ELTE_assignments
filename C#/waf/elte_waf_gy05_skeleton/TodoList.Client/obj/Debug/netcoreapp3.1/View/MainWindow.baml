   M S B A M L   `   `   `  ����J  FTodoList.Client, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null1clr-namespace:TodoList.ClientTodoList.Client  5   	        TodoList.Client.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35e aSystem.Windows.Controls.Ribbon, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   /localclr-namespace:TodoList.Client     5   	     � Title$  
MainWindow��5   	   $	��450��6   $	��800��6)   .��5	      � .+�5
   
   �� $��
0,25,0,325q�6   ��6&   �� *Lists+ �� SelectedIndex 6D   �� *
CurrListId+��5      �� 5      .R�5      �� ��6    �� *Name+68   5      5      &   System.Windows.Controls.DataGrid  5   
   $��	0,141,0,0q�6      AutoGenerateColumns$ False��6C   ��6&   �� *Rows+   Columns 5      4  .System.Windows.Controls.DataGridTemplateColumn  5      ,  &System.Windows.Controls.DataGridColumn   Header$ Image��6)      CellTemplate 5      �� 5      .R�5      �� ��6$   �� *Image+6?   5      5      0  *System.Windows.Controls.DataGridTextColumn  5      $
 Name��6%   1  +System.Windows.Controls.DataGridBoundColumn   Binding 63   �� *Name+  5      $ Deadline��6%    67   �� *
Deadline+  5      $ Description��6%    6:   �� *Description+5      �� 5   
   $��Lists:��6   $
��Left=�6!   $	��Top=�6<   $��10,0,0,0q�6T   �� 5    
   $��Items:��6   $
��Left=�6!   $	��Top=�6<   $��
10,114,0,0q�6T    J� RenderTransformOrigin$ -0.099,0.62&�6h   5!      5"      