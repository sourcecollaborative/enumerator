# enumerator
Enumerator enumerates columns in a selected subset of rows from a data file 
for diagnostic purposes. Enumerator automatically detects the most common
column separator characters (commas, tabs, pipe characters,semicolons, and colons)
and prints the ordinals using circled digits and double-struck digits. When
printed directly to the terminal, the ordinals will be printed in color so
they are easily distinguishable from the data in the file. When output is
redirected to a file, the ordinals still appear distinct from the data
because Unicode circled digits and double-struck digits are used.
