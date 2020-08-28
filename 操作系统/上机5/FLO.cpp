#include <iostream>
#include <fstream>
using namespace std;

int *memory = new int[3]; //-1 means no page in this memory page,using * to reperesent
int *page = new int[12];  //pages
int pm = 0;               //pointer of memory
int count = 0;            //missing page count
int *replace = new int[12];
int pr = 0;
int sizeM;
int sizeP;

void title()
{
    cout << "引用号, 帧序列" << endl;
}
void clear()
{
    for (int i = 0; i < sizeM; i++)
    {
        memory[i] = -1;
    }
    pr = 0;
    pm = 0;
    count = 0;
    //cout<<"All clear."<<endl;
}
void outPutArr(int i)
{
    cout << page[i] << ",  | ";
    for (int j = 0; j < sizeM; j++)
    {
        if (memory[j] == -1)
            cout << "*  ";
        else
            cout << memory[j] << "  ";
    }
    cout << "|" << endl;
}
void outPut()
{
    cout << "-------------------" << endl;
    cout << "帧错误次数 = " << count << endl;
    /*cout << "repalce pages are  : ";
    for (int i = 0; i < pr; i++)
    {
        cout << replace[i] << " ";
    }
    cout << endl;*/
    //cout << "the rate of page lack is " << count / double(sizeP) * 100 << "%" << endl;
    cout<<endl;
}
void FIFO()
{
    cout << "-----FIFO-----" << endl;
    title();
    //search begin
    for (int i = 0; i < sizeP; i++)
    {
        //check if there is page[i] in memory
        bool exist = false;
        for (int j = 0; j < sizeM; j++)
        {
            if (page[i] == memory[j])
            {
                exist = true;
                break;
            }
        }
        //not exist , replace this memory page
        if (exist == false)
        {
            if (memory[pm] != -1)
            {
                replace[pr] = memory[pm];
                pr++;
            }

            count++;
            memory[pm] = page[i];
            pm++;
            if (pm == sizeM)
                pm = 0;
        }
        outPutArr(i);
    }
    outPut();
}

void LRU()
{
    cout << "-----LRU-----" << endl;
    title();
    //search begin
    for (int i = 0; i < sizeP; i++)
    {
        //there are sizeM memory pages in memory ,so if i<sizeM,just put it in memory
        if (i < sizeM)
        {
            memory[i] = page[i];
            count++;
        }
        else
        {
            //check if this page is in memory already
            bool exist = false;
            for (int j = 0; j < sizeM; j++)
            {
                if (page[i] == memory[j])
                {
                    exist = true;
                    break;
                }
            }

            if (exist == false)
            {
                //begin to choose a memory page to replace
                int last = 0;
                bool ok[3];
                for (int j = 0; j < sizeM; j++)
                    ok[j] = false;

                //check from i step -1 till 0
                for (int j = i; j >= 0; j--)
                {
                    for (int k = 0; k < sizeM; k++)
                    {
                        if (page[j] == memory[k])
                        {
                            ok[k] = true;
                            last++;
                            break;
                        }
                    }
                    if (last == 2)
                        break;
                }
                //check which ok ==false
                for (int j = 0; j < sizeM; j++)
                {
                    if (ok[j] == false)
                    {
                        //replace this memory[j]
                        count++;
                        replace[pr] = memory[j];
                        pr++;
                        memory[j] = page[i];
                        break;
                    }
                }
            }
        }

        outPutArr(i);
    }
    outPut();
}

void OPT()
{
    cout << "-----OPT-----" << endl;
    title();
    //search begin
    for (int i = 0; i < sizeP; i++)
    {
        if (i < sizeM)
        {
            memory[i] = page[i];
            count++;
        }
        else
        {
            //check if this page is in memory already
            bool exist = false;
            for (int j = 0; j < sizeM; j++)
            {
                if (page[i] == memory[j])
                {
                    exist = true;
                    break;
                }
            }

            if (exist == false)
            {
                //begin to choose a memory page to replace
                int later = 0;
                bool ok[3];
                for (int j = 0; j < sizeM; j++)
                    ok[j] = false;

                //check from i step -1 till 0
                for (int j = i + 1; j < sizeP; j++)
                {
                    for (int k = 0; k < sizeM; k++)
                    {
                        if (page[j] == memory[k])
                        {
                            ok[k] = true;
                            later++;
                            break;
                        }
                    }
                    if (later == 2)
                        break;
                }
                //check which ok ==false
                for (int j = 0; j < sizeM; j++)
                {
                    if (ok[j] == false)
                    {
                        //replace this memory[j]
                        count++;
                        replace[pr] = memory[j];
                        pr++;
                        memory[j] = page[i];
                        break;
                    }
                }
            }
        }
        outPutArr(i);
    }
    outPut();
}

int main()
{
    ifstream inFile("page.txt");
    inFile >> sizeM;
    inFile >> sizeP;
    for (int i = 0; i < sizeM; i++)
    {
        memory[i] = -1;
    }
    for (int i = 0; i < sizeP; i++)
    {
        inFile >> page[i];
    }
    FIFO();
    clear();
    LRU();
    clear();
    OPT();
    return 0;
}
