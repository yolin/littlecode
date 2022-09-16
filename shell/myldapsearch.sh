#!/bin/sh

ad_host="192.168.60.100:389"
ad_admin="xxxx"
ad_pwd="0000"
ad_binddn="dc=xxx,dc=com"

search_group_dn()
{
    for i in "$@"
    do
        echo "===>search[$i]"

        local group_dn_ldif=$(ldapsearch -o ldif-wrap=no -LLL -x -h $ad_host -D "$ad_admin" -w "$ad_pwd" -b "$ad_binddn" "(&(objectCategory=group)(cn=$i))" dn |grep ^dn: | head -1)

        if [ "$group_dn_ldif" != "" ]
        then
            group_dn=${group_dn_ldif#* }

            if [ -n "$group_dn" ]
            then
                if [ "${group_dn_ldif:0:4}" = "dn::" ]
                then
                    is_base64=1
                    decode_group_dn=$(echo "$group_dn" | openssl base64 -d)
                else
                    is_base64=0
                fi

                echo "==>found dn [${group_dn}]"
                if [ $is_base64 -eq 1 ]
                then
                    echo "==>found dn [${decode_group_dn}]"
                fi
            fi

        fi


    done
}


search_group_dn "$@"
