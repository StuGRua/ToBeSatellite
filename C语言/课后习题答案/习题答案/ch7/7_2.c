/*�ж�ĳ���Ƿ����ڷ������ͣ���ʹ��"��ָ��"ָ��*/
#include<stdio.h>
int main()
{
	float fWeight;  /*����*/
	float fHeight;  /*���*/
	float fT;

	printf("Input your weight(m):");
	scanf("%f",&fWeight);
    printf("Input your Height(kg):");
	scanf("%f",&fHeight);

	fT=fWeight/(fHeight*fHeight);

	/*�ü�if���ʵ�ֵ�ѡ��ṹ*/
	if(fT<18)
	{
			printf("Lower weight!\n");
	}
	if(fT>=18 && fT<25)
	{
		printf("Standard weight!\n");
	}
	if(fT>=25 && fT<27)
	{
		printf("Highter weight!\n");
	}
	if(fT>=27)
	{
	    printf("Too fat!!\n");
	}
/*
	/*�ü�ifǶ�����ʵ��˫ѡ��ṹ*/
	if(fT<27)
	{
		if(fT<25)
		{
			if(fT<18)
				cout<<"Lower weight!"<<endl;
		
	    	else
			{
			    cout<<"Standard weight!"<<endl;
			}
		}
	   else
	   {
		cout<<"Highter weight!"<<endl;
	   }
	}
	else
	{
		cout<<"Too fat!!"<<endl;
	}

	/*��if-else���ʵ�ֶ���ṹ*/
	if(fT<18)
	{
		cout<<"Lower weight!"<<endl;
	}
	else if (fT<25)
	{
		cout<<"Standard weight!"<<endl;
	}
	else if(fT<27)
	{
		cout<<"Highter weight!"<<endl;
	}
	else
	{
		cout<<"Too fat!!"<<endl;
	}
*/	
	return 0;
}