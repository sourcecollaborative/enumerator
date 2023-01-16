# enumerator

Enumerator is a command-line tool that enumerates columns in a 
selected subset of rows from a data file for diagnostic purposes. 

## Features

Enumerator automatically detects the most common
column separator characters (*commas, tabs, pipe characters,semicolons, and colons*)
so you don't have to tell the tool what type of separator is used.

When printing a row from a file, the tool prefixes each column of data
with an ordinal which is printed using Unicode circled digits and 
double-struck digits.

When printed directly to the terminal, the ordinals are printed in color so
they are easily distinguishable from the data in the file. When output is
redirected to a file, the ordinals still appear distinct from the data
because Unicode circled digits and double-struck digits are visibly 
quite distinct from normal ASCII digits.
