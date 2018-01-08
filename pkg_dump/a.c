
void pkt_dump(uint8_t *data,int len,const char *dir,int unit)
{
    int i;
    for (i=0; i<=len; i++)
    {
        if (i == 0)
            printk("%s mac:%d: len:%d ->\n",dir,unit,len);

        printk("%2X:",data[i]);

        if (!(i%20))
            printk("\n");
    }
}

