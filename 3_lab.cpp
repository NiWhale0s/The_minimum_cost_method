#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <iomanip>
#include <windows.h>

using namespace std;

int n, m;
ifstream in;

vector<vector<int>> file_reader_matrix_init(string file_path)
{    
    in.open(file_path);
    bool for_n_m = true;
    if (in.is_open())
    {
        if (for_n_m)
        {
            in >> m >> n;
            for_n_m = false;
            vector<vector<int>> matrix (m, vector<int>(n));
            return matrix;
        }
    }  
}

void file_reader_matrix_fill(vector<vector<int>>& to_fill)
{
    int temp;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == m-1 && j == n-1)
            {
                to_fill[i][j] = 0;
                in.close();
                return;
            }
            in >> temp;
            to_fill[i][j] = temp;
        }
    }
    in.close();  
}

void Print_matrix(vector<vector<int>> matrix){

    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int l = matrix.size();
    int c = matrix[0].size();
    for(int i=0; i<c; i++){
        if (i == c-1){
            break;
        }
        cout << setw(4) << "B" <<i+1;
    }
    cout<<endl;
    
    for (int i = 0; i < l; i++)
    {
        if (i!= l-1){
            cout<<"A"<<i+1<<setw(3);
        }
        for (int j = 0; j < c; j++)
        {       
                if (i == l-1 && j == c-1){
                    SetConsoleTextAttribute(hconsole, 9);
                    cout << setw(5) << matrix[i][j];
                    SetConsoleTextAttribute(hconsole, 7);
                }
                else if (i== l-1){ 
                    SetConsoleTextAttribute(hconsole, 10);
                    cout << setw(5) << matrix[i][j];
                    SetConsoleTextAttribute(hconsole, 7);
                }
                else if (matrix[i][j] == -2 && j==0) cout << "-";
                else if (j==0) cout << matrix[i][j];
                else if (j==c-1){ 
                    SetConsoleTextAttribute(hconsole, 10);
                    cout << setw(5) << matrix[i][j];
                    SetConsoleTextAttribute(hconsole, 7);
                }
                else if (matrix[i][j] == -2) {cout << setw(5) << "-";}

                else cout << setw(5) << matrix[i][j]; 
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> Check_matrix_to_start(vector<vector<int>> matrix){
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int sum_column=0; 
    int sum_line=0;
        for (int j=0;j < n; j++){
            sum_column+=matrix[m-1][j];
        } 
    for (int i=0; i < m ; i++){
        
            sum_line+=matrix[i][n-1];
         
    }

    cout<<endl<<"Column="<<sum_column<<"  "<<"Line="<<sum_line<<endl;

    if (sum_column < sum_line){
        SetConsoleTextAttribute(hconsole, 12);
        cout<<"Sum column < sum Line!!!"<<endl;
        SetConsoleTextAttribute(hconsole, 7);
        
        vector<vector<int>> new_matrix (m, vector<int>(n+1));
        for (int i=0; i<m; i++){
            for (int j=0; j<n+1; j++){
                if (j <= n-2) {
                    new_matrix[i][j] = matrix[i][j];
                }
                if (j == n-1){
                    new_matrix[i][j] = 0;
                }
                if (j == n){
                    new_matrix[i][j] = matrix[i][j-1];
                }
                //cout<<new_matrix[i][j]<<" ";
            }
        }
        new_matrix[m-1][n-1] = sum_line - sum_column;
        new_matrix[m-1][n] = sum_line;
        Print_matrix(new_matrix);
        return new_matrix;
    }

    if (sum_line < sum_column){
        SetConsoleTextAttribute(hconsole, 12);
        cout<<"Sum line < sum column!!!!"<<endl<<endl;
        SetConsoleTextAttribute(hconsole, 7);
        vector<vector<int>> new_matrix (m+1, vector<int>(n));

        for (int i=0;i<m+1;i++){
            for (int j=0; j<n; j++){
                if (i<m-1){
                    new_matrix[i][j] = matrix[i][j];
                }
                if (i == m-1){
                    new_matrix[i][j] = 0;
                }
                if (i == m){
                    new_matrix[i][j] = matrix[i-1][j];
                }
            }
        }
        new_matrix[m-1][n-1] = sum_column - sum_line;
        new_matrix[m][n-1] = sum_column; 
        //Print_matrix(new_matrix, m+1, n);
        return new_matrix;
    }

    if (sum_column == sum_line){
        SetConsoleTextAttribute(hconsole, 10);
        cout<<endl<<"Sum line = sum column!!!!"<<endl<<endl;
        SetConsoleTextAttribute(hconsole, 7);
        matrix[m-1][n-1] = sum_line;
        //Print_matrix(matrix, m, n);
        return matrix;
    }
}

int min_el_n=1000;
int min_el_m=1000;

int check_to_done = 0;
int all_check_to_done = 0;


void Print_method_matrix(vector<vector<int>> matrix, vector<vector<int>> new_matrix){

    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int l = matrix.size();
    int c = matrix[0].size();
    for(int i=0; i<c; i++){
        if (i == c-1){
            break;
        }
        cout << setw(4) << "B" <<i+1;
    }
    cout<<setw(16)<<"B1";
    for(int i=1; i<c; i++){
        if (i == c-1){
            break;
        }
        cout << setw(4) << "B" <<i+1;
    }
    cout<<endl;
    
    for (int i = 0; i < l; i++)
    {
        if (i!= l-1){
            cout<<"A"<<i+1<<setw(3);
        }
        for (int j = 0; j < c; j++)
        {       
                if (min_el_m == i && min_el_n == j && matrix[min_el_m][min_el_n] != -1){
                    SetConsoleTextAttribute(hconsole, 6);
                    cout <<setw(5)<< matrix[i][j];
                    SetConsoleTextAttribute(hconsole, 7);
                }  
                else if (i == l-1 && j == c-1){
                    SetConsoleTextAttribute(hconsole, 9);
                    if (matrix[i][j] == -2){
                        cout << setw(5) << "?";    
                    }
                    else if (matrix[i][j] == -1){
                        cout << setw(5) << "-";
                    }
                    else{
                    cout << setw(6) << matrix[i][j];
                    }
                    SetConsoleTextAttribute(hconsole, 7);
                }
                else if (i== l-1 && j == 0){
                    SetConsoleTextAttribute(hconsole, 10);
                    if (matrix[i][j] == -2){
                        cout << setw(5) << "?";    
                    }
                    else if (matrix[i][j] == -1){
                        cout << setw(5) << "-";
                    }
                    else{
                        cout <<setw(5)<< matrix[i][j];
                    }
                    SetConsoleTextAttribute(hconsole, 7);
                }
                else if (i== l-1){ 
                    SetConsoleTextAttribute(hconsole, 10);
                    if (matrix[i][j] == -2){
                        cout << setw(5) << "?";    
                    }
                    else if (matrix[i][j] == -1){
                        cout << setw(5) << "-";
                    }
                    else{
                        cout << setw(5) << matrix[i][j];
                    }
                    SetConsoleTextAttribute(hconsole, 7);
                }
                else if (j==0){ 
                    if (matrix[i][j] == -2){
                        cout<<"?";    
                    }
                    else if (matrix[i][j] == -1){
                        cout<<"-";
                    }
                    else{
                        cout << matrix[i][j];
                    }
                }
                else if (j==c-1){ 
                    SetConsoleTextAttribute(hconsole, 10);
                    if (matrix[i][j] == -2){
                        cout << setw(5) << "?";    
                    }
                    else if (matrix[i][j] == -1){
                        cout << setw(5) << "-";
                    }
                    else {
                        cout << setw(5) << matrix[i][j];
                    }
                    SetConsoleTextAttribute(hconsole, 7);
                }
                else{
                    if (matrix[i][j] == -2){
                        cout << setw(5) <<"?";    
                    }
                    else if (matrix[i][j] == -1){
                        cout << setw(5) <<"-";
                    }
                    else{
                        cout << setw(5) << matrix[i][j];
                    }
                }

            
        }

        if (i!= l-1){
            cout<<setw(7)<<"A"<<i+1<<setw(3);
        }
        for (int j = 0; j < c; j++)
        {       
                if (i == l-1 && j == c-1){
                    SetConsoleTextAttribute(hconsole, 9);
                    if (new_matrix[i][j] == -2){
                        cout << setw(5) << "?";    
                    }
                    else if (new_matrix[i][j] == -1){
                        cout << setw(5) << "-";
                    }
                    else{
                    cout << setw(5) << new_matrix[i][j];
                    }
                    SetConsoleTextAttribute(hconsole, 7);
                }
                else if (i== l-1 && j == 0){
                    SetConsoleTextAttribute(hconsole, 10);
                    if (new_matrix[i][j] == -2){
                        cout << setw(5) << "?";    
                    }
                    else if (new_matrix[i][j] == -1){
                        cout << setw(5) << "-";
                    }
                    else{
                        cout << setw(11) << new_matrix[i][j];
                    }
                    SetConsoleTextAttribute(hconsole, 7);
                }
                else if (i== l-1){ 
                    SetConsoleTextAttribute(hconsole, 10);
                    if (new_matrix[i][j] == -2){
                        cout << setw(5) << "?";    
                    }
                    else if (new_matrix[i][j] == -1){
                        cout << setw(5) << "-";
                    }
                    else{
                        cout << setw(5) << new_matrix[i][j];
                    }
                    SetConsoleTextAttribute(hconsole, 7);
                }
                else if (j==0){ 
                    if (new_matrix[i][j] == -2){
                        cout<<"?";    
                    }
                    else if (new_matrix[i][j] == -1){
                        cout<<"-";
                    }
                    else{
                        cout << new_matrix[i][j];
                    }
                }
                else if (j==c-1){ 
                    SetConsoleTextAttribute(hconsole, 10);
                    if (new_matrix[i][j] == -2){
                        cout << setw(5) << "?";    
                    }
                    else if (new_matrix[i][j] == -1){
                        cout << setw(5) << "-";
                    }
                    else {
                        cout << setw(5) << new_matrix[i][j];
                    }
                    SetConsoleTextAttribute(hconsole, 7);
                }
                else{
                    if (new_matrix[i][j] == -2){
                        cout << setw(5) <<"?";    
                    }
                    else if (new_matrix[i][j] == -1){
                        cout << setw(5) <<"-";
                    }
                    else{
                        cout << setw(5) << new_matrix[i][j];
                    }
                }
            
        }
        cout << endl;
    }
    cout << endl;
}

void Find_min_el(vector<vector<int>> matrix, int flag){
    //if  m n
    if (flag == 0){
        for (int i=0; i<matrix.size()-1;i++){
            for (int j=0; j<matrix[0].size()-1; j++){
               if (matrix[i][j]>0){
                    min_el_m = i;
                    min_el_n = j;
                    break;
               } 
            }
        }
    }
    
    if (flag == 0){
        for (int i=0; i<matrix.size()-1;i++){
            for (int j=0; j<matrix[0].size()-1; j++){
               if ((matrix[min_el_m][min_el_n] > matrix[i][j]) && matrix[i][j] > 0){
                    min_el_m = i;
                    min_el_n = j;
               } 
            }
        }
    }
    // if m n+1
    else if (flag == 1){
        
        
        for (int i=0; i<matrix.size()-1;i++){
            for (int j=0; j<matrix[0].size()-2; j++){
               if (matrix[i][j]>0){
                    min_el_m = i;
                    min_el_n = j;
                    break;
               } 
            }
        }
    


        for (int i=0; i<matrix.size()-1;i++){
            for (int j=0; j<matrix[0].size()-2; j++){
                if ((matrix[min_el_m][min_el_n] > matrix[i][j]) && matrix[i][j] > 0){
                    min_el_m = i;
                    min_el_n = j;
               } 
            }
        }
    }
    // if m+1 n
    else {

        for (int i=0; i<matrix.size()-1;i++){
            for (int j=0; j<matrix[0].size()-2; j++){
               if (matrix[i][j]>0){
                    min_el_m = i;
                    min_el_n = j;
                    break;
               } 
            }
        }


        for (int i=0; i<matrix.size()-2;i++){
            for (int j=0; j<matrix[0].size()-1; j++){
                if ((matrix[min_el_m][min_el_n] > matrix[i][j]) && matrix[i][j] > 0){
                    min_el_m = i;
                    min_el_n = j;
               }  
            }   
        }
    }

}

void Check_to_done(vector<vector<int>> matrix, int flag){
    if (flag == 0){
    for (int i=0; i<matrix.size()-1; i++){
            for (int j=0;j< matrix[i].size()-1;j++){
                if (matrix[i][j] == -1){
                    check_to_done++;
                }
            }
        }
    }

    else if (flag == 1){
    for (int i=0; i<matrix.size()-1; i++){
            for (int j=0;j< matrix[i].size()-2;j++){
                if (matrix[i][j] == -1){
                    check_to_done++;
                }
            }
        }
    }

    else {
    for (int i=0; i<matrix.size()-2; i++){
            for (int j=0;j< matrix[i].size()-1;j++){
                if (matrix[i][j] == -1){
                    check_to_done++;
                }
            }
        }
    }
}

void Number_substitution_algorithm(vector<vector<int>>& matrix, vector<vector<int>>& new_matrix, int flag){
    if (flag == 0){
        if (matrix[min_el_m][n-1] < matrix[m-1][min_el_n]){
            new_matrix[min_el_m][min_el_n] = matrix[min_el_m][n-1];
            for (int i=0;i<n-1;i++){
                matrix[min_el_m][i] = -1;
            }
            matrix[m-1][min_el_n] = matrix[m-1][min_el_n] - matrix[min_el_m][n-1];
            matrix[min_el_m][n-1] = 0;

       }
       else if (matrix[min_el_m][n-1] > matrix[m-1][min_el_n]){
            new_matrix[min_el_m][min_el_n] = matrix[m-1][min_el_n];
            for(int i=0;i<m-1;i++){
                matrix[i][min_el_n] = -1;
            }
            matrix[min_el_m][n-1] = matrix[min_el_m][n-1] - matrix[m-1][min_el_n];
            matrix[m-1][min_el_n] = 0;  
       }
       else {
           new_matrix[min_el_m][min_el_n] = matrix[min_el_m][n-1];
            for (int i=0;i<n-1;i++){
                if (new_matrix[min_el_m][i] == -2){
                    new_matrix[min_el_m][i] = 0;
                    break;
                }
            }
            for (int i=0;i<n-1;i++){
                matrix[min_el_m][i] = -1;
            }
            for(int i=0;i<m-1;i++){
                matrix[i][min_el_n] = -1;
            }
            
            matrix[m-1][min_el_n] = 0;  
            matrix[min_el_m][n-1] = 0;
       }

    }
    else if (flag == 1){
        if (matrix[min_el_m][n] < matrix[m-1][min_el_n]){
            new_matrix[min_el_m][min_el_n] = matrix[min_el_m][n];
            for (int i=0;i<n;i++){
                matrix[min_el_m][i] = -1;
            }
            matrix[m-1][min_el_n] = matrix[m-1][min_el_n] - matrix[min_el_m][n];
            matrix[min_el_m][n] = 0;

       }
       else if (matrix[min_el_m][n] > matrix[m-1][min_el_n]){
            new_matrix[min_el_m][min_el_n] = matrix[m-1][min_el_n];
            for(int i=0;i<m-1;i++){
                matrix[i][min_el_n] = -1;
            }
            matrix[min_el_m][n] = matrix[min_el_m][n] - matrix[m-1][min_el_n];
            matrix[m-1][min_el_n] = 0;  
       }
       else {
           new_matrix[min_el_m][min_el_n] = matrix[min_el_m][n];
            for (int i=0;i<n;i++){
                matrix[min_el_m][i] = -1;
            }
            for(int i=0;i<m-1;i++){
                matrix[i][min_el_n] = -1;
            }
            for (int i=0;i<n-1;i++){
                if (new_matrix[min_el_m][i] == -2){
                    new_matrix[min_el_m][i] = 0;
                    break;
                }
            }
            matrix[m-1][min_el_n] = 0;  
            matrix[min_el_m][n] = 0;
       }

    }
    else {
       if (matrix[min_el_m][n-1] < matrix[m][min_el_n]){
            new_matrix[min_el_m][min_el_n] = matrix[min_el_m][n-1];
            for (int i=0;i<n-1;i++){
                matrix[min_el_m][i] = -1;
            }
            matrix[m][min_el_n] = matrix[m][min_el_n] - matrix[min_el_m][n-1];
            matrix[min_el_m][n-1] = 0;

       }
       else if (matrix[min_el_m][n-1] > matrix[m][min_el_n]){
            new_matrix[min_el_m][min_el_n] = matrix[m][min_el_n];
            for(int i=0;i<m;i++){
                matrix[i][min_el_n] = -1;
            }
            matrix[min_el_m][n-1] = matrix[min_el_m][n-1] - matrix[m][min_el_n];
            matrix[m][min_el_n] = 0;  
       }
       else {
           new_matrix[min_el_m][min_el_n] = matrix[min_el_m][n-1];
            for (int i=0;i<n-1;i++){
                matrix[min_el_m][i] = -1;
            }
            for(int i=0;i<m;i++){
                matrix[i][min_el_n] = -1;
            }
            for (int i=0;i<n-1;i++){
                if (new_matrix[min_el_m][i] == -2){
                    new_matrix[min_el_m][i] = 0;
                    break;
                }
            }
            matrix[m][min_el_n] = 0;  
            matrix[min_el_m][n-1] = 0;
       } 
    }
}

void Check_matrix_to_finish(vector<vector<int>>& matrix, vector<vector<int>>& new_matrix){
    //cout<<"Reshenie:"<<endl;
    for (int i=0;i<matrix.size()-1;i++){
        for (int j=0;j<matrix[0].size()-1;j++){
            if (matrix[i][j] == 0){
                if (matrix[i][matrix[0].size()-1] == matrix[matrix.size()-1][j]){
                    new_matrix[i][j] = matrix[i][matrix[0].size()-1];
                    matrix[i][matrix[0].size()-1] = 0;
                    matrix[matrix.size()-1][j] = 0;
                }
                else if (matrix[i][matrix[0].size()-1] < matrix[matrix.size()-1][j]){
                    new_matrix[i][j] = matrix[i][matrix[0].size()-1];
                    matrix[matrix.size()-1][j] = matrix[matrix.size()-1][j] - matrix[i][matrix[0].size()-1];
                    matrix[i][matrix[0].size()-1] = 0;
                }
                else {
                    new_matrix[i][j] = matrix[matrix.size()-1][j];
                    matrix[i][matrix[0].size()-1] = matrix[i][matrix[0].size()-1] - matrix[matrix.size()-1][j];
                    matrix[matrix.size()-1][j] = 0;
                }
                //cout<<matrix[i][matrix[0].size()-1]<<" "<<matrix[matrix.size()-1][j];
            }
            
            
        }
        //cout<<check_sum_numb_prac<<endl;
    }
    
}

vector<vector<int>> The_minimum_cost_method(vector<vector<int>> matrix){
    //-1 - ?
    //-2 - -
    if (matrix.size() == m  && matrix[0].size() == n){
        vector<vector<int>> new_matrix = matrix;
        for (int i=0; i<m-1; i++){
            for (int j=0;j<n-1;j++){
                new_matrix[i][j] = -2;
            }
        }
        while(true){
        Check_to_done(matrix, 0);
        if (check_to_done == all_check_to_done){
            break;
        }
        check_to_done = 0;
            Find_min_el(matrix, 0);
            Print_method_matrix(matrix, new_matrix);
            Number_substitution_algorithm(matrix, new_matrix, 0);
            Print_method_matrix(matrix, new_matrix);
            cout<<"______________________________"<<endl;
        }
        Check_matrix_to_finish(matrix, new_matrix);
        return new_matrix;
    }
    //m n+1
    else if (matrix.size() == m && matrix[0].size() == n+1){
        vector<vector<int>> new_matrix = matrix;
        for (int i=0; i<m-1; i++){
            for (int j=0;j<n;j++){
                new_matrix[i][j] = -2;
            }
        }
        while(true){
        Check_to_done(matrix, 1);
        if (check_to_done == all_check_to_done){
            break;
        }
        check_to_done = 0;
            Find_min_el(matrix, 1);
            Print_method_matrix(matrix, new_matrix);
            Number_substitution_algorithm(matrix, new_matrix, 1);
            Print_method_matrix(matrix, new_matrix);
            cout<<"______________________________"<<endl;
        }
       Check_matrix_to_finish(matrix, new_matrix);
      return new_matrix;  
    }
    //m+1 n
    else {
        vector<vector<int>> new_matrix = matrix;
        for (int i=0; i<m; i++){
            for (int j=0;j<n-1;j++){
                new_matrix[i][j] = -2;
            }
        }
        while(true){
        Check_to_done(matrix, 2);
        if (check_to_done == all_check_to_done){
            break;
        }
        check_to_done = 0;
            Find_min_el(matrix, 2);
            Print_method_matrix(matrix, new_matrix);
            Number_substitution_algorithm(matrix, new_matrix, 2);
            Print_method_matrix(matrix, new_matrix);
            cout<<"______________________________"<<endl;
        }
        Check_matrix_to_finish(matrix, new_matrix);  
        return new_matrix;
    }
}

void Degenerate_plan(vector<vector<int>> matrix){
    int check_degenerate = (matrix.size()-1)+(matrix[0].size()-1)-1;
    int check_sum_numb = 0;
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i=0;i<matrix.size()-1;i++){
        for (int j=0;j<matrix[0].size()-1;j++){
            if(matrix[i][j] >= 0){
                check_sum_numb++;
            }
        }
    }
    if (check_sum_numb >= check_degenerate){
        SetConsoleTextAttribute(hconsole, 10);
        cout<<"Degenerate not!"<<endl<<"Reshenie:"<<endl;
        SetConsoleTextAttribute(hconsole, 7);
        Print_matrix(matrix);
    }
    else {
        SetConsoleTextAttribute(hconsole, 12);
        cout<<"Degenerate!"<<endl;
        SetConsoleTextAttribute(hconsole, 7);
        for (int i=0;i<matrix.size()-1;i++){
            for (int j=0;j<matrix[0].size()-1;j++){
                if(matrix[i][j] == -2){
                    matrix[i][j]=0;
                    check_sum_numb++;
                }
                if (check_sum_numb == check_degenerate){
                    Print_matrix(matrix);
                    return;
                }
        }
    }
    }
}

int main(int arc, char* argv[])
{   
    setlocale(LC_ALL, "Russian");

    vector<vector<int>> matrix = file_reader_matrix_init(argv[1]);

    file_reader_matrix_fill(matrix); 
    
    Print_matrix(matrix);

    vector<vector<int>> new_matrix = Check_matrix_to_start(matrix);

    Print_matrix(new_matrix);
    all_check_to_done = (n-1)*(m-1);
    //cout<<new_matrix.size()<<endl;
    //cout<<new_matrix[0].size()<<endl;
    new_matrix = The_minimum_cost_method(new_matrix);
    //Print_matrix(new_matrix);
    Degenerate_plan(new_matrix);

    int sum = 0;
    for (int i=0;i<matrix.size()-1;i++){
        for (int j=0;j<matrix[0].size()-1;j++){
            if(new_matrix[i][j] > 0){
                sum = sum+new_matrix[i][j]*matrix[i][j];
            }
        }
    }
    cout<<endl<< "Sum = "<< sum;
    //cout << "V matrize " << m-1 << " postawtschikov and " << n-1 << " potrebiteley" << endl; 
    
    return 0;
}