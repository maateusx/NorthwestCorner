#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<iostream>
#include<iomanip>

#define MAX 50

using namespace std;
enum boolean{
    FALSE,
    TRUE
};

class cantoNoroeste{
    int data[MAX][MAX];
    int requered[MAX];
    int capacity[MAX];
    int allocation[MAX][MAX];
    int linhas, colunas, no_of_allocation;
    public:cantoNoroeste(){
            for(int i=0; i<MAX; i++){
                capacity[i]=0;
                requered[i]=0;
                for(int j=0; j<MAX; j++){
                    data[i][j]=0;
                    allocation[i][j]=0;
                }
            }
            linhas=colunas = no_of_allocation=0;
        }

        //Define tamanho da coluna
        void setaColuna(int col){
            colunas = col;
        };

        //Define tamanho da linha
        void setaLinha(int lin){
            linhas = lin;
        };

        //Popula matriz com os custos
        void populaCustos();

        //Popula matriz com ofertas
        void populaOfertas();

        //Popula matriz com demandas
        void populaDemandas();

        //Otimiza matriz
        void otimizaMatriz();

        void alocaMatriz();

        boolean checkValue(int [],int);
        void display();
};

boolean cantoNoroeste :: checkValue(int arr[],int no){
    for(int i=0;i<no;i++)
        if(arr[i]!=0)
            return FALSE;
    return TRUE;
}

void duplicaVetor(int tam, int vet1[], int vet2[]){
    int i, j;
    int inicial1, inicial2;
    inicial1 = inicial2 = 0;

    for(i = inicial1, j = inicial2; i< tam; i++, j++){
        vet2[j] = vet1[i];
    }
}

int getTotal(int array[],int no){
    int sum=0;
    for(int i=0;i<no;i++)
        sum+=array[i];
    return sum;
}

void cantoNoroeste :: alocaMatriz(){
    int i=0,j=0;
    int temp_requered[MAX]={0};
    int temp_capacity[MAX]={0};
    int sum_of_cap,sum_of_req;
    sum_of_cap=getTotal(capacity,linhas);
    sum_of_req=getTotal(requered,colunas);
    if(sum_of_cap!=sum_of_req){
        if(sum_of_cap>sum_of_req){
            for(j=0;j<linhas;j++)
                data[j][colunas]=0;
            requered[colunas]=sum_of_cap-sum_of_req;
            colunas++;
        }
        else{
            for(j=0;j<colunas;j++)
                data[linhas][j]=0;
            capacity[linhas]=sum_of_req-sum_of_cap;
            linhas++;
        }
    }
    i=j=0;
    duplicaVetor(linhas, capacity, temp_capacity);
    duplicaVetor(colunas, requered, temp_requered);
    while(!checkValue(temp_capacity,linhas) || !checkValue(temp_requered,colunas)){
        if(temp_capacity[i]>temp_requered[j]){
            allocation[i][j]=temp_requered[j];
            temp_capacity[i]-=temp_requered[j];
            temp_requered[j]=0;
            j++;
        }
        else if(temp_capacity[i]<temp_requered[j]){
            allocation[i][j]=temp_capacity[i];
            temp_requered[j]-=temp_capacity[i];
            temp_capacity[i]=0;
            i++;
        }
        else{
            allocation[i][j]=temp_capacity[i];
            temp_capacity[i]=temp_requered[j]=0;
            i++;
            j++;
        }
        no_of_allocation++;
    }
}

///POPULA MATRIZ COM AS OFERTAS
void cantoNoroeste :: populaOfertas(){
    int i;
    system("cls");
    cout << "\n --- OFERTAS --- \n";

    for(i=0; i<linhas; i++){
        cout << "Entre com a oferta #" << i+1 << ": ";
        cin >> capacity[i];
    }
}

///POPULA MATRIZ COM AS DEMANDAS
void cantoNoroeste :: populaDemandas(){
    int i;

    system("cls");
    cout << "\n --- DEMANDAS --- \n";

    for(i=0; i<colunas; i++){
        cout << "Entra com a demanada #" << i+1 <<": ";
        cin >> requered[i];
    }
}

void cantoNoroeste :: display(){
    int i;
    cout<<"\n";
    cout<<setw(9);
    for(i=0;i<colunas;i++)
        cout<<"D"<<i+1<<setw(4);
    cout<<setw(5)<<"Oferta"<<endl<<setw(0);
    for(i=0;i<linhas;i++){
        cout<<setw(3)<<"S"<<i+1;
        for(int j=0;j<colunas;j++)
            cout<<setw(5)<<data[i][j];
        cout<<setw(5)<<capacity[i]<<endl;
    }
    cout<<setw(4)<<"Demanda:";
    for(i=0;i<colunas;i++)
        cout<<setw(5)<<requered[i];

    cout<<"\n\nApos a alocacao:\n";
    for(i=0;i<linhas;i++){
        for(int j=0;j<colunas;j++){
            if(allocation[i][j]!=0)
                cout<<"\t"<<data[i][j]<<"["<<allocation[i][j]<<"]";
            else
                cout<<"\t"<<data[i][j];
        }
        cout<<endl;
    }
    int k=0,sum=0;
    for(i=0;i<linhas;i++){
        for(int j=0;j<colunas;j++){
            if(allocation[i][j]!=0){
                //cout<<"("<<data[i][j]<<"*"<<allocation[i][j]<<")";
                if(k<no_of_allocation-1){
                    //cout<<"+";
                    k++;
                }
                sum+=data[i][j]*allocation[i][j];
            }
        }
    }
    cout<<"\nanswer : "<<sum;
    if((linhas+colunas-1)==no_of_allocation){
        cout<<"\nEssa eh uma solucao nao otimizada!";
    }
    else{
        cout<<"\nEssa eh uma solucao nao otimizada!";
    }
}

///POPULA MATRIZ COM OS CUSTOS
void cantoNoroeste :: populaCustos(){
    int i, j;
    system("cls");
    cout << "\n --- Insira os dados da matriz ---" << endl;

    for(i=0; i<linhas; i++){
        cout << "Insira o custo de transbordo da linha " << i << ":\n";
        for(j=0; j<colunas; j++){
            cin >> data[i][j];
        }
    }
}

void cantoNoroeste :: otimizaMatriz(){
    int ot_lin[linhas], ot_col[colunas];
    int ultimo = 0;

    for(int i = 0; i < linhas; i++){
        for(int k = 0; k< colunas; k++){
            if(i == 0 && k == 0){
                ot_lin[0] = 0;
            }
            if(allocation[i][k]!=0){
                if(ultimo == 0) {
                    ot_col[k] = data[i][k] - ot_lin[i];
                    //printf("\n 1V: %d\n" , ot_col[k]);
                } else if(ultimo == 1) {
                    ot_lin[i] = data[i][k] - ot_col[k];
                    //printf("\n 2U: %d\n" , ot_lin[i]);
                    ultimo = 0;
                }
            }
        }
        if(ultimo == 0)
            ultimo = 1;
        else
            ultimo = 0;
    }

    printf("\n\n Calculo das novas cedulas:\n");
    //calcula novas celulas
    int cal_basico[linhas][colunas];
    for(int i=0; i < linhas; i++){
        for(int k = 0; k< colunas; k++){
            if(allocation[i][k]!=0){
                cal_basico[i][k] = allocation[i][k];
            }
            else{
                cal_basico[i][k] = data[i][k] - ot_col[k] - ot_lin[i];
            }
            printf("%d[%d] ", data[i][k], cal_basico[i][k]);
        }
        printf("\n");
    }

    /// começa aqui parte do loop
    int menor_value = 0;
    int menor_x = 0; int menor_y = 0;
    for(int i=0; i < linhas; i++){
        for(int k = 0; k< colunas; k++){
            if(cal_basico[i][k] < menor_value){
                 menor_value = cal_basico[i][k];
                 menor_x = i;
                 menor_y = k;
            }
        }
    }
    if(menor_value == 0){
        printf("Solucao otimazada\n\n\n\n");
    }

    int x = menor_x, y = menor_y;
    int loop = 0;
    int menor_vizinho = -1;
    int mv_x = 0, mv_y = 0;
    while(loop == 0){
        if((x > 0) && (y > 0) && (x < linhas-1) && (y < colunas-1)){
          if(allocation[x+1][y] != 0){
            if(menor_vizinho == -1 || menor_vizinho >= allocation[x+1][y]){
                menor_vizinho = allocation[x+1][y];
                mv_x = x+1;
                mv_y = y;
            }
          }
          if(allocation[x][y+1] != 0){
            if(menor_vizinho == -1 || menor_vizinho >= allocation[x][y+1]){
                menor_vizinho = allocation[x][y+1];
                mv_x = x;
                mv_y = y+1;
            }
          }
          if(allocation[x-1][y] != 0){
             if(menor_vizinho == -1 || menor_vizinho >= allocation[x-1][y]){
                menor_vizinho = allocation[x-1][y];
                mv_x = x-1;
                mv_y = y;
            }
          }
          if(allocation[x][y-1] != 0){
             if(menor_vizinho == -1 || menor_vizinho >= allocation[x][y-1]){
                menor_vizinho = allocation[x][y-1];
                mv_x = x;
                mv_y = y-1;
            }
          }
        } else {

        }
    }

}

int main(){

    cantoNoroeste m1;
    int num_lin, num_col;
    cout << "Digite o tamanho da matriz(N x M), apenas o numero de transbordos: ";
    cin >> num_lin;
    cin >> num_col;

    m1.setaColuna(num_col); // Define a quantidade de colunas
    m1.setaLinha(num_lin); // Define a quantidade de linhas

    m1.populaCustos(); // Popula os custos na matriz
    m1.populaOfertas(); // `Popula as ofertas na matriz
    m1.populaDemandas(); // Popula as demandas na matriz

    m1.alocaMatriz();

    m1.display();

    m1.otimizaMatriz();

    getch();
}
