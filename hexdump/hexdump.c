
static void hexdump(int level, const char *title, const u8 *buf, size_t len)
{
    size_t i;
    printf("%s - hexdump(len=%lu):", title, (unsigned long) len);
    if (buf == NULL) {
        printf(" [NULL]");
    } else {
        for (i = 0; i < len; i++)
            printf(" %02x", buf[i]);
    }
    printf("\n");
}
