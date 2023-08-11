txt = "MOVE grap catch move "
text = txt.lower()
counter0 = 0
counter1 = 0
counter2 = 0

for i in range (len(text)) : 
    if ( text[i] == 'm' )  :
        if ( text[i+1] =='o' and text[i+2] == 'v' and text[i+3] == 'e' ) :
            counter0 += 1
            print ( "move" )
    elif ( text[i] == 'g' )  :
        if ( text[i+1] == 'r' and text [i+2] =='a' and text [i+3] == 'p' ) :
            counter1 += 1
            print ("grap")
    elif ( text[i] == 'c' )  :
        if ( text[i+1] =='a' and text[i+2]=='t' and text[i+3] == 'c' and text[i+4] == 'h' ) :
            counter2 =+ 1
            print( "catch" )
print( counter0 , counter1 , counter2 )
[12:38 PM]
txt = "MOVE grap catch move bye bye "
text = txt.lower()
counter0 = 0
counter1 = 0
counter2 = 0

for i in range (len(text)) : 
    if ( text[i] == 'm' )  :
        if ( text[i+1] =='o' and text[i+2] == 'v' or text[i+3] == 'e' ) :
            counter0 += 1
            print ( "move" )
    elif ( text[i] == 'g' )  :
        if ( text[i+1] == 'r' and text [i+2] =='a' and text [i+3] == 'p' ) :
            counter1 += 1
            print ("grap")
    elif ( text[i] == 'b' )  :
        if ( text[i+1] =='y' and text[i+2]=='e' ) :
            counter2 =+ 1
            print( "bye" )
print( counter0 , counter1 , counter2 )