str="    aaa    bbb    ccc    "

echo "$str" | sed -e "s/^[ ]*//g" | sed -e "s/[ ]*$//g"
