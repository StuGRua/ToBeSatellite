#include<iostream>
#include<fstream>
using namespace std;

int h_start=0;
int m_start=0;
int mission;
int time_piece;
int wait_time;
char w;
class process
{
public:
    int index;
    int exe_time;
    int h;
    int m;
    int priority;
    char mark;
    process()
    {
        mark='0';
    }
};

void FCFS(process pro[])
{
    process temp;
    process pro1[5];
    int i=0,j=0;
    int key;
    h_start=8;
    m_start=0;
    wait_time=0;
    for(; i<5; i++)
        pro1[i]=pro[i];
    //按申请时间先后对5个进程进行排序
    for(i=0; i<4; i++)
    {
        key=i;
        for(j=i+1; j<5; j++)
            if((pro1[j].h*60+pro1[j].m) < (pro1[key].h*60+pro1[key].m))
                key=j;
        temp=pro1[key];
        pro1[key]=pro1[i];
        pro1[i]=temp;
    }
    cout<<"FCFS:"<<endl;
    for(i=0; i<5; i++)
    {
        wait_time+=h_start*60+m_start-pro1[i].h*60-pro1[i].m;
        cout<<pro1[i].index<<' '<<h_start<<':'<<m_start<<' ';
        m_start+=pro1[i].exe_time;
        if(m_start>=60)
        {
            h_start++;
            m_start-=60;
        }
        cout<<h_start<<':'<<m_start<<endl;
    }
    wait_time/=5;
    cout<<"Average waiting time:"<<wait_time<<endl;
}
void SJF(process pro [])
{
    process pro1[5];
    process pro2[5];
    process temp;
    int n2=0;
    int i=0,j=0;
    int key=0;
    int out=0;
    h_start=8;
    m_start=0;
    wait_time=0;
    for(i=0; i<5; i++)
        pro1[i]=pro[i];
    cout<<"SJF(非抢占):"<<endl;
    while(out<5)
    {
        //将pro1中满足条件的进程加入到等待序列pro2中
        for(i=0; i<5; i++)
        {
            if(pro1[i].mark=='0' && (pro1[i].h*60+pro1[i].m)<=(h_start*60+m_start))
            {
                pro2[n2++]=pro1[i];
                pro1[i].mark='1';
            }
        }
        //对等待序列pro2中的进程按照执行时间从小到大排序
        for(i=0; i<n2-1; i++)
        {
            key=i;
            for(j=i+1; j<n2; j++)
                if(pro2[j].exe_time < pro2[key].exe_time)
                    key=j;
            temp=pro2[key];
            pro2[key]=pro2[i];
            pro2[i]=temp;
        }
        //对排序后的序列进行执行
        wait_time+=h_start*60+m_start-pro2[0].h*60-pro2[0].m;
        cout<<pro2[0].index<<' '<<h_start<<':'<<m_start<<' ';
        m_start+=pro2[0].exe_time;
        if(m_start>60)
        {
            h_start++;
            m_start-=60;
        }
        cout<<h_start<<':'<<m_start<<endl;
        n2--;
        out++;
        //清除执行完成的进程
        for(i=0; i<n2; i++)
            pro2[i]=pro2[i+1];
    }
    wait_time/=5;
    cout<<"Average waiting time:"<<wait_time<<endl;
}
void PRO(process pro[])
{
    process pro1[5];
    process pro2[5];
    process temp;
    int n2=0;
    int i=0,j=0;
    int key=0;
    int out=0;
    h_start=8;
    m_start=0;
    wait_time=0;
    for(i=0; i<5; i++)
        pro1[i]=pro[i];
    cout<<"优先级调度(非抢占):"<<endl;
    while(out<5)
    {
        //将pro1中满足条件的进程加入到等待序列pro2中
        for(i=0; i<5; i++)
        {
            if(pro1[i].mark=='0' && (pro1[i].h*60+pro1[i].m)<=(h_start*60+m_start))
            {
                pro2[n2++]=pro1[i];
                pro1[i].mark='1';
            }
        }
        //对等待序列pro2中的进程按照优先级排序
        for(i=0; i<n2-1; i++)
        {
            key=i;
            for(j=i+1; j<n2; j++)
                if(pro2[j].priority < pro2[key].priority)
                    key=j;
            temp=pro2[key];
            pro2[key]=pro2[i];
            pro2[i]=temp;
        }
        //对排序后的序列进行执行
        wait_time+=h_start*60+m_start-pro2[0].h*60-pro2[0].m;
        cout<<pro2[0].index<<' '<<h_start<<':'<<m_start<<' ';
        m_start+=pro2[0].exe_time;
        if(m_start>60)
        {
            h_start++;
            m_start-=60;
        }
        cout<<h_start<<':'<<m_start<<endl;
        n2--;
        out++;
        //清除执行完成的进程
        for(i=0; i<n2; i++)
            pro2[i]=pro2[i+1];
    }
    wait_time/=5;
    cout<<"Average waiting time:"<<wait_time<<endl;
}
void RR(process pro[])
{
    process temp;
    process pro1[5];
    int i=0,j=0;
    int key=0,n1=5,n2=1;
    int exet[5];
    h_start=8;
    m_start=0;
    wait_time=0;
    for(; i<5; i++)
        pro1[i]=pro[i];
    for(i=0; i<5; i++)
        exet[i]=pro1[i].exe_time;
    //按申请时间先后对5个进程进行排序
    for(i=0; i<4; i++)
    {
        key=i;
        for(j=i+1; j<5; j++)
            if((pro1[j].h*60+pro1[j].m) < (pro1[key].h*60+pro1[key].m))
                key=j;
        temp=pro1[key];
        pro1[key]=pro1[i];
        pro1[i]=temp;
    }
    cout<<"RR:"<<endl;
    //开始执行,mark=0：未等待 mark=1：等待 mark=2：执行结束
    while(n1>0)
    {
        for(i=0; i<5; i++)
        {
            if(pro1[i].mark=='2')continue;
            pro1[i].mark='1';
            cout<<pro1[i].index<<' '<<h_start<<':'<<m_start<<' ';
            //时间片不够用
            if(pro1[i].exe_time>time_piece)
            {
                pro1[i].exe_time-=time_piece;
                m_start+=time_piece;
                if(m_start>=60)
                {
                    h_start++;
                    m_start-=60;
                }
                cout<<h_start<<':'<<m_start<<endl;
                //判断下一个进程是否处于等待状态
                if(i+1==n1)i=-1;
                else
                {
                    if((h_start*60+m_start)<(pro1[i+1].h*60+pro1[i+1].m))
                        i=-1;
                    // else if(pro1[i+1].mark=='0')n2++;
                }
            }
            //时间片够用
            else
            {
                m_start+=pro1[i].exe_time;
                if(m_start>=60)
                {
                    h_start++;
                    m_start-=60;
                }
                cout<<h_start<<':'<<m_start<<endl;
                n1--;
                //n2--;
                //清除执行结束的程序
                //for(j=i;j<n1;j++)
                //pro1[j]=pro1[j+1];
                pro1[i].mark='2';
                wait_time+=h_start*60+m_start-exet[i]-pro1[i].h*60-pro1[i].m;
                //判断下一个进程是否处于等待状态
                if(i+1==n1)i=-1;
                else
                {
                    if((h_start*60+m_start)<(pro1[i+1].h*60+pro1[i+1].m))
                        i=-1;
                    //else if(pro1[i+1].mark=='0'){n2++;i--;}
                }
            }
        }
    }
    wait_time/=5;
    cout<<"Average waiting time:"<<wait_time<<endl;
}

int main()
{
    process p[5];
    ifstream inFile("job.txt");
    inFile>>mission;
    inFile>>time_piece;
    for(int i=0; i<5; i++)
    {
        inFile>>p[i].index;
        inFile>>p[i].h;
        inFile>>w;
        inFile>>p[i].m;
        inFile>>p[i].exe_time;
        inFile>>p[i].priority;
    }
    FCFS(p);
    SJF(p);
    PRO(p);
    RR(p);
    inFile.close();
    return 0;
}