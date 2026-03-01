# include <stdio.h>
typedef struct {
short numero ;
char libelle[29] ;
short quantite ;
float prix ;
}Article;
Article articlee;
void SaisieArticle(Article* article){
     printf("\nsaiser le numero d'article : ");
     scanf("%hd",&article->numero);
     printf("\nsaiser la libelle  d'article : ");
     scanf("%s",article->libelle);
     printf("\nsaiser la quantite  d'article : ");
     scanf("%hd",&article->quantite);
     printf("\nsaiser le prix d'article : ");
     scanf("%f",&article->prix);
}
void AfficheArticle(Article article){
     printf("\n\n\n======affiche les information d'article est=====\n\n\n -----numeru : %hd\n -------libelle : %s\n ------quantite : %hd\n ------prix : %.2f \n",article.numero,article.libelle,article.quantite,article.prix);
}
void SaisieTabArticle(Article article[], int n ){
    for (int i = 0;i<n;i++){
       printf("\n=====le champs capable de saiser les informations d'article [%d]======\n",i+1);
      SaisieArticle(&articlee);
      article[i]=articlee;
      
    }
}
void AfficheTabStock(Article article[], int n ){
    for (int i = 0;i<n;i++){
       if(article[i].quantite > 150 ) {
         printf("le champs des informations d'article.[%d]\n",i+1);
         articlee=article[i];
         AfficheArticle(articlee);   
      }
    }
}
int main(){
   int n ;
   printf("saiser nombre d'article vous devez remplir :");
   scanf("%d",&n);
   Article article[n];
   SaisieTabArticle(article,n);
   AfficheTabStock(article, n );
}
