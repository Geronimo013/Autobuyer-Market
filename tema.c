#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista_supermarket 
{
	char* nume;
	char* categorie;
	int pret;
	int cantitate;
	int stoc;
	struct lista_supermarket *next;
}LS;

typedef struct lista_cumparaturi
{
	char* nume;
	char* categorie;
	int cantitate; 
	struct lista_cumparaturi *next;
}LC;

typedef struct cumparaturi
{
	char* nume;
	char* categorie;
	int cantitate; 
	struct cumparaturi *next;
}C;
//1
void citire_LS(LS **nod,FILE *f)
{
    (*nod)->nume=(char*) malloc(25*sizeof(char));
    (*nod)->categorie=(char*) malloc(25*sizeof(char));
    fscanf(f,"%s",(*nod)->nume);
    fscanf(f,"%s",(*nod)->categorie);
    fscanf(f,"%d",&((*nod)->pret));
    fscanf(f,"%d",&((*nod)->cantitate));
    fscanf(f,"%d",&((*nod)->stoc));
}

void adaugare_LS(LS **head,FILE *f)
{
    LS *new_nod,*aux;
    new_nod=*head;
    aux=*head;
    while(new_nod!=NULL)
    {
        aux=new_nod;
        new_nod=new_nod->next;
    }
    if(aux==NULL)
    {
        new_nod=(LS*) malloc(sizeof(LS));
        citire_LS(&new_nod,f);
        new_nod->next=*head;
        *head=new_nod;
    }
  	else
    {
        new_nod=(LS*) malloc(sizeof(LS));
        citire_LS(&new_nod,f);
        new_nod->next=NULL;
        aux->next=new_nod;
    }
}

void citire_LC(LC **nod,FILE *f)
{
    (*nod)->nume=(char*) malloc(25*sizeof(char));
    (*nod)->categorie=(char*) malloc(25*sizeof(char));
    fscanf(f,"%s",(*nod)->nume);
    fscanf(f,"%s",(*nod)->categorie);
    fscanf(f,"%d",&((*nod)->cantitate));
}

void adaugare_LC(LC **head,FILE *f)
{
   	LC *new_nod,*aux;
    new_nod=*head;
    aux=*head;
    while(new_nod!=NULL)
    {
        aux=new_nod;
        new_nod=new_nod->next;
    }
    if(aux==NULL)
    {
        new_nod=(LC*) malloc(sizeof(LC));
        citire_LC(&new_nod,f);
        new_nod->next=*head;
        *head=new_nod;
    }
    else
    {
        new_nod=(LC*) malloc(sizeof(LC));
        citire_LC(&new_nod,f);
        new_nod->next=NULL;
        aux->next=new_nod;
    }

}
//2
void elim(LC *p)
{
    LC *q;
    q=p->next;
    p->next=p->next->next;
    free(q);
}

void eliminare1 (LS *headLS,LC **headLC, int *n)
{

 LS *q;
 LC *p;

 for(q=headLS; q!=NULL; q=q->next)
	{
		while(strcmp((*headLC)->nume,q->nume)==0 && q->stoc==0)
  			{
      			if((*headLC)->next==NULL)
      				{
          				free(*headLC);
          				(*headLC)=NULL;
          				*n=(*n)-1;
          				break;
      				}
      			p=(*headLC)->next;
      			free(*headLC);
      			(*headLC)=p;
  			}
  		if((*headLC)!=NULL)
  			for(p=(*headLC);p->next!=NULL;p=p->next)
    			{
     				while(strcmp(p->next->nume,q->nume)==0 && q->stoc==0)
       					{
         					elim(p);
         					if(p->next==NULL)
         						{
         							*n=(*n)-1;
           							break;
           						}
       					}
      				if(p->next==NULL)
      					{
      						*n=(*n)-1;
        					break;
    					}
    			}
 
	}
}

//3
void copiere2(LC *a,C *b)
{
	b->nume=(char*)malloc(25*sizeof(char));
	strcpy(b->nume,a->nume);
	b->categorie=(char*)malloc(25*sizeof(char));
	strcpy(b->categorie,a->categorie);
}
 /*void copiere1(LC *a,C *b,int x)
{
	b->nume=(char*)malloc(25*sizeof(char));
	strcpy(b->nume,a->nume);
	b->categorie=(char*)malloc(25*sizeof(char));
	strcpy(b->categorie,a->categorie);
	b->cantitate=x;
}*/

C* cumparaturi1(LS *headLS, LC* headLC, int buget)
{
	LS *q;
	LC *p;
	C *t=NULL,*nou=NULL;
	int x=0,d;

	
	for(p=headLC; p!=NULL; p=p->next)
	{
		for(q=headLS; q!=NULL; q=q->next)
			if(strcmp(q->nume,p->nume)==0 && q->stoc==1)
			{
				if(p->cantitate<=q->cantitate && x<=buget)
				{  	
					if(nou==NULL)
					{
						nou=(C*)malloc(sizeof(C));
						copiere2(p,nou);
						for(d=0;(x+(d*(q->pret)))<=buget && d<=p->cantitate;d++)
							nou->cantitate=d;
						nou->next=NULL;
						t=nou;
						x=x+(nou->cantitate)*(q->pret);
					}
					else
					{	
						t->next=(C*)malloc(sizeof(C));
						t=t->next;
						copiere2(p,t);
						for(d=0;(x+(d*(q->pret)))<=buget && d<=p->cantitate;d++)
							t->cantitate=d;
						t->next=NULL;
						x=x+(t->cantitate)*(q->pret);
					}
				}
				else
				{
					if(nou==NULL)
					{
						nou=(C*)malloc(sizeof(C));
						copiere2(p,nou);
						for(d=0;(x+(d*(q->pret)))<=buget;d++)
							nou->cantitate=d;
						nou->next=NULL;
						t=nou;
						x=x + (nou->cantitate)*(q->pret);
					}
					else
					{
						t->next=(C*)malloc(sizeof(C));
						t=t->next;
						copiere2(p,t);
						for(d=0;(x+(d*(q->pret)))<=buget;d++)
							t->cantitate=d;
						t->next=NULL;
						x=x + (t->cantitate)*(q->pret);
					}
				}
			}
	}
	return nou;
}

//4
/*void sortare(LS**head, LS *nou)
{
    LS *tmp_node = NULL;
 
    if(*head == NULL || nou->pret < (*head)->pret)
    {
        nou->next = *head;
        *head = nou;
        return;
    }
 
        tmp_node = *head;
 
    while(tmp_node->next && nou->pret> tmp_node->next->pret)
    {
        tmp_node = tmp_node->next;
    }
 
    nou->next = tmp_node->next;
    tmp_node->next = nou;
}

void sortare_pret(LS **headLS)
{
    LS *nou = NULL;
    LS *tmp = *headLS;
    LS *tmp1 = NULL;

    	while(tmp)
    	{
        	tmp1 = tmp;
        	tmp = tmp->next;
        	sortare(&nou, tmp1);
    	}
    *headLS = nou;
}

C* cumparaturi2(LS *headLS, LC** headLC)
{
	LS *q;
	LC *p,*r=*headLC;
	int n;
	C *t=NULL,*nou=NULL;
	int x=0;

	for(p=*headLC; p!=NULL; p=p->next)
	{
		for(q=headLS; q!=NULL; q=q->next)
				
				{

					
				}
	}

	return nou;
}*/
//5
/*typedef struct arbore
{
	int cant;
	struct arbore *st,*dr;
}ARB;

void nod(ARB **rad,int x)
{
	if( NULL == *rad )
    {
        *rad = (ARB*) malloc( sizeof(ARB));
        (*rad)->cant = x;
        (*rad)->st = NULL;    
        (*rad)->dr = NULL;  
    }
    else if(x < (*rad)->cant)
    {
        nod( &(*rad)->st,x );
    }
    else if(x > (*rad)->cant)
    {
        nod(  &(*rad)->dr,x );
    }
}

ARB* creare_arbore(C *headC)
{	
	C *p;
	ARB *rad;
	rad=(ARB*)malloc(sizeof(ARB));
	for(p=headC;p!=NULL;p=p->next)
	{
		nod(&rad,p->cantitate);
	}
	return rad;
}
void afisare_arbore(ARB *rad,FILE *f)
{
	if (rad)
	{
		fprintf(f,"%d ",rad->cant);
		afisare_arbore(rad->st,f);
		afisare_arbore(rad->dr,f);
	}
}*/

//6
typedef struct stiva
{
	int vf;
	int capacitate;
	int *v;
}sti;

sti* creare_stiva(int x)
{
	sti *s=(sti*)malloc(sizeof(sti));
	if (!s) return NULL; 
		s->capacitate=x;

	s->vf=-1;

	s->v= (int*) malloc(sizeof(int)*s->capacitate);
	if (!s->v) 
		return NULL;
	return s;
}

void adaugare_s(sti *s, int x)
{
	s->v[++s->vf]=x; 
}

void comparare(sti **s,LS *headLS)
{
	LS *p,*q;
	int k=0;
	for(p=headLS; p!=NULL; p=p->next)
		{	k=0;
			for(q=headLS; q!=p; q=q->next)
			{
				if(p->pret < q->pret)
				{
					k++;
				}
				else
				{
					k=0;
				}
			}
		adaugare_s(*s,k);
		}
}


int main(int argc, char *argv[])
{
	LS *L1=NULL,*d,*L1a=NULL;
	LC *L2=NULL, *p;
	C *L3=NULL, *q;
	FILE *da1, *da2, *cer, *out;
	//ARB* arb;
	sti* s;
	da1=fopen(argv[1],"rt");
    da2=fopen(argv[2],"rt");
    cer=fopen(argv[3],"rt");
    out=fopen(argv[4],"wt");

    int nLS,nLC,i;
    fscanf(da1,"%d",&nLS);
    fscanf(da2,"%d",&nLC);
 	int cer1,cer2,cer3,cer4,cer5,cer6,buget;
 	fscanf(cer,"%d%d%d%d%d%d",&cer1,&cer2,&cer3,&cer4,&cer5,&cer6);
 	fscanf(cer,"%d",&buget);

for(i=0;i<nLS;i++)
    adaugare_LS(&L1,da1);

 		if(cer1==1)
    	 	for(i=0;i<nLC;i++)
        		adaugare_LC(&L2,da2);

    	if(cer2==1)	
            eliminare1(L1,&L2,&nLC);

   	 	if(cer3==1)
    		L3=cumparaturi1(L1,L2,buget);

    	/*if(cer4==1)
			{
				for(i=0;i<nLS;i++)
    				adaugare_LS(&L1a,da1);
				sortare_pret(&L1a);
				L3==cumparaturi2(L1a,&L2);
			}*/
    	/*if(cer5==1)
    	{
    		arb=creare_arbore(L3);
    	}*/


    	if(cer6==1)
    	{
    		s=creare_stiva(nLS);
    	}
    		


		if(cer1==1 || cer2==1)
			{
			for(p=L2;p!=NULL;p=p->next)
    			{
    				fprintf(out,"%s %s %d\n",p->nume,p->categorie,p->cantitate);
    			}
			fprintf(out,"\n");
			}
    	if(cer3==1 || cer4==1)
    		{
    		for(q=L3;q!=NULL;q=q->next)
    			{
    				fprintf(out,"%s %s %d\n",q->nume,q->categorie,q->cantitate);
    			}
    		fprintf(out,"\n");
    		}
    	/*if(cer5==1)
    		{
    			afisare_arbore(arb,out);
    		fprintf(out,"\n");
    		}*/
    	if(cer6==1)
    		{	
    			comparare(&s,L1);
    		for( i=0;i<nLS;i++)
    			{	
    				fprintf(out,"%d ",s->v[i]);
    			}
    		fprintf(out,"\n");
    		}

    
	fclose(da1);
	fclose(da2);
	fclose(cer);
	fclose(out);
	return 0;

}