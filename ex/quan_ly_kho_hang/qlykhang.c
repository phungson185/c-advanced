#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"libfdr/jrb.h"
#include"libfdr/jval.h"
#include"igraph/igraph.h"
#include"DebugPrintf/debug_printf.h"
#define MAX 30
typedef struct kho
{
    char ten_kho[MAX];
    int id_kho;
}kho;
typedef struct qlykho
{
    kho data;
    int id_san_pham[MAX];
    int so_luong_san_pham[MAX];
}qlykho;

typedef struct duongdi
{
    int id1[MAX];
    int id2[MAX];
    int kc[MAX];
}duongdi;
int so_loai_san_pham;
int main(int argc, char *argv[])
{
    JRB tensanpham_id = make_jrb();
    JRB id_tensanpham = make_jrb();
    char name[MAX];
    int id;
    FILE*p = fopen("sanpham.txt","r");
    fscanf(p,"%d",&so_loai_san_pham);
    while (fscanf(p,"%s",name)!= EOF)
    {
        fscanf(p,"%d",&id);
        jrb_insert_str(tensanpham_id,strdup(name),(Jval){.i = id});
        jrb_insert_int(id_tensanpham,id,(Jval){.s = strdup(name)});
    }
    fclose(p);
    if(strcmp(argv[1],"-t")==0)
    {
        printf("C-Advanced,HK20182\n");
        return 0;
    }
    else if(strcmp(argv[1],"-s")==0)
    {
        FILE*p = fopen(argv[2],"r");
        fscanf(p,"%d",&so_loai_san_pham);
        while (fscanf(p,"%s",name)!= EOF)
        {
            fscanf(p,"%d",&id);
            jrb_insert_str(tensanpham_id,strdup(name),(Jval){.i = id});
            jrb_insert_int(id_tensanpham,id,(Jval){.s = strdup(name)});
        }
        fclose(p);
        for(JRB ptr = jrb_first(id_tensanpham);ptr != jrb_nil(id_tensanpham);ptr = jrb_next(ptr))
        {
            printf("%s %d\n",ptr->val.s,ptr->key.i);
        }
    }
    else if(strcmp(argv[1],"-w")==0)
    {
        FILE*p = fopen(argv[2],"r");
        int count_kho = 0;
        int count_sp = 0;
        int check =0;
        int id1 = atoi(argv[3]);
        int id2 = atoi(argv[4]);
        int so_luong_kho_hang;
        int so_luong_duong_di;
        qlykho quan_ly_kho[MAX];
        duongdi ptr;
        if(jrb_find_int(id_tensanpham,id1)==NULL || jrb_find_int(id_tensanpham,id2)==NULL)
            {
                printf("-1\n");
                return -1;
            }
        fscanf(p,"%d",&so_luong_kho_hang);
        while(count_kho != so_luong_kho_hang)
        {
            count_kho++;
            fscanf(p,"%s",quan_ly_kho[count_kho].data.ten_kho);
            fscanf(p,"%d",&quan_ly_kho[count_kho].data.id_kho);
            while(count_sp != so_loai_san_pham)
                {
                    count_sp++;
                    fscanf(p,"%d",&quan_ly_kho[count_kho].id_san_pham[count_sp]);
                    fscanf(p,"%d",&quan_ly_kho[count_kho].so_luong_san_pham[count_sp]);
                }
            count_sp = 0;
        }
        /*for(int i = 1;i<=count_kho;i++)
        {
            printf("%s %d\n",quan_ly_kho[i].data.ten_kho,quan_ly_kho[i].data.id_kho);
            printf("%d %d\n",quan_ly_kho[i].id_san_pham[1],quan_ly_kho[i].so_luong_san_pham[1]);
            printf("%d %d\n",quan_ly_kho[i].id_san_pham[2],quan_ly_kho[i].so_luong_san_pham[2]);
            printf("%d %d\n",quan_ly_kho[i].id_san_pham[3],quan_ly_kho[i].so_luong_san_pham[3]);
        }*/
        fscanf(p,"%d",&so_luong_duong_di);
        int i = 1;
        while(fscanf(p,"%d",&ptr.id1[i])!=EOF)
        {
            fscanf(p,"%d",&ptr.id2[i]);
            fscanf(p,"%d",&ptr.kc[i]);
            i++;
        }
        fclose(p);
        for(int h = 1; h < i ; h++)
        {
            if(ptr.id1[h] == id1 && ptr.id2[h] == id2)
            {
                printf("%d km\n",ptr.kc[h]);
                check = 1;
            }
        }
        if(check == 0)
            printf("-1\n");
    }
    else if(strcmp(argv[1],"-a")==0)
    {
        FILE*p = fopen(argv[3],"r");
        fscanf(p,"%d",&so_loai_san_pham);
        while (fscanf(p,"%s",name)!= EOF)
        {
            fscanf(p,"%d",&id);
            jrb_insert_str(tensanpham_id,strdup(name),(Jval){.i = id});
            jrb_insert_int(id_tensanpham,id,(Jval){.s = strdup(name)});
        }
        fclose(p);
        FILE*h = fopen(argv[2],"r");
        int count_kho = 0;
        int count_sp = 0;
        int so_luong_kho_hang;
        int so_luong_duong_di;
        qlykho quan_ly_kho[MAX];
        duongdi ptr;
        fscanf(h,"%d",&so_luong_kho_hang);
        while(count_kho != so_luong_kho_hang)
        {
            count_kho++;
            fscanf(h,"%s",quan_ly_kho[count_kho].data.ten_kho);
            fscanf(h,"%d",&quan_ly_kho[count_kho].data.id_kho);
            while(count_sp != so_loai_san_pham)
                {
                    count_sp++;
                    fscanf(h,"%d",&quan_ly_kho[count_kho].id_san_pham[count_sp]);
                    fscanf(h,"%d",&quan_ly_kho[count_kho].so_luong_san_pham[count_sp]);
                }
            count_sp = 0;
        }
        fscanf(h,"%d",&so_luong_duong_di);
        int i = 1;
        while(fscanf(h,"%d",&ptr.id1[i])!=EOF)
        {
            fscanf(h,"%d",&ptr.id2[i]);
            fscanf(h,"%d",&ptr.kc[i]);
            i++;
        }
        fclose(h);
        i = 0;
        int k =0;
        while(i!=so_luong_kho_hang)
        {
            i++;
            printf("%s\n",quan_ly_kho[i].data.ten_kho);
            while(k!=so_loai_san_pham)
            {
                k++;
                printf("%s %d\n",jrb_find_int(id_tensanpham,quan_ly_kho[i].id_san_pham[k])->val.s,quan_ly_kho[i].so_luong_san_pham[k]);
            }
            k=0;
            if(i!= so_loai_san_pham)
                printf(".....\n");
        }
    }
    else if(strcmp(argv[1],"-h")==0)
    {
        FILE*p = fopen(argv[3],"r");
        fscanf(p,"%d",&so_loai_san_pham);
        while (fscanf(p,"%s",name)!= EOF)
        {
            fscanf(p,"%d",&id);
            jrb_insert_str(tensanpham_id,strdup(name),(Jval){.i = id});
            jrb_insert_int(id_tensanpham,id,(Jval){.s = strdup(name)});
        }
        fclose(p);
        FILE*h = fopen(argv[2],"r");
        int count_kho = 0;
        int count_sp = 0;
        int so_luong_kho_hang;
        int so_luong_duong_di;
        qlykho quan_ly_kho[MAX];
        duongdi ptr;
        fscanf(h,"%d",&so_luong_kho_hang);
        while(count_kho != so_luong_kho_hang)
        {
            count_kho++;
            fscanf(h,"%s",quan_ly_kho[count_kho].data.ten_kho);
            fscanf(h,"%d",&quan_ly_kho[count_kho].data.id_kho);
            while(count_sp != so_loai_san_pham)
                {
                    count_sp++;
                    fscanf(h,"%d",&quan_ly_kho[count_kho].id_san_pham[count_sp]);
                    fscanf(h,"%d",&quan_ly_kho[count_kho].so_luong_san_pham[count_sp]);
                }
            count_sp = 0;
        }
        fscanf(h,"%d",&so_luong_duong_di);
        int i = 1;
        while(fscanf(h,"%d",&ptr.id1[i])!=EOF)
        {
            fscanf(h,"%d",&ptr.id2[i]);
            fscanf(h,"%d",&ptr.kc[i]);
            i++;
        }
        fclose(h);
        int ma_san_pham = atoi(argv[4]);
        int ma_kho_hang = atoi(argv[5]);
        printf("%s\n",quan_ly_kho[ma_kho_hang].data.ten_kho);
        printf("%s %d\n",jrb_find_int(id_tensanpham,ma_san_pham)->val.s,quan_ly_kho[ma_kho_hang].so_luong_san_pham[ma_san_pham]);
        printf("---Cac kho ke la:\n");
        for(i = 0;i<=so_luong_kho_hang;i++)
        {
            if(ptr.id1[i] == ma_kho_hang)
                {
                    printf("%s\n",quan_ly_kho[ptr.id2[i]].data.ten_kho);
                    printf("%s %d\n",jrb_find_int(id_tensanpham,ma_san_pham)->val.s,quan_ly_kho[ptr.id2[i]].so_luong_san_pham[ma_san_pham]);
                }
            if(ptr.id2[i] == ma_kho_hang)
                {
                    printf("%s\n",quan_ly_kho[ptr.id1[i]].data.ten_kho);
                    printf("%s %d\n",jrb_find_int(id_tensanpham,ma_san_pham)->val.s,quan_ly_kho[ptr.id1[i]].so_luong_san_pham[ma_san_pham]);
                }
        }
    }
}