# Black-Windows-Titlebars
This tool sets the accent color for title bars on Windows 10 to a pitch black color, as Windows 10 only allows for a dark-ish grey at best. This doesn't touch the color chosen in personalization options, just the title bar, so border colors, start menu colors, taskbar colors, and the rest are all unaffected, so you can combine a color of choice with a black title bar, e.g. pink on black, or yellow on black. 

This is actually a pretty trivial task, as all you need to do is just modify a registry key, and it can be done manually through the Registry Editor, however I wanted to make this tool since it's easier to invoke from the command line whenever the changes reset, a service can be made out of it, and so that I don't have to note down and remember the key & value that needs to be modified. I also just like to program.

The registry key in question can be found here

`HKEY_CURRENT_USER\Software\Microsoft\Windows\DWM`

Where the `AccentColor` value should be changed to 010101, (01 for R, G, and B which is the lowest R, G, and B value other than 00, which Windows interprets as grey rather than black for some reason.)