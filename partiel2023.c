#include <stdio.h>
#include <stdlib.h>


typedef struct{
    int fact;
    int nbOcc;
}FactPremier;

typedef struct cellule{
    FactPremier donnee;
    struct cellule *suivant;
}*ListeDFP;

typedef struct {
    ListeDFP tete;
    ListeDFP queue;
}ListeTQ_DFP;




void insertion(ListeTQ_DFP *liste, int fat, int occ){
    ListeDFP nouvelle = (ListeDFP)malloc(sizeof(struct cellule));
    nouvelle->donnee.fact=fat;
    nouvelle->donnee.nbOcc=occ;
    nouvelle->suivant=NULL;
    if(liste->tete==NULL){
        liste->queue=nouvelle;
        liste->tete=nouvelle;
    }
    else{
        liste->queue->suivant=nouvelle;
        liste->queue=nouvelle;
    }
}

ListeTQ_DFP decomposition(int nombre){
    ListeTQ_DFP resultat ={NULL,NULL};
    int fact=2;
    while(nombre>1){
        int occ=0;
        while(nombre%fact==0){
            nombre/=fact;
            occ++;
        }
            if(occ>0)
            {insertion(&resultat,fact,occ);}
            fact++;
        }
return resultat;
}
      

ListeDFP rechercher(ListeTQ_DFP *liste){
    ListeDFP courant=liste->tete;
    ListeDFP resultat=NULL;
    
    int plusOcc=0;
    if(courant==NULL){
        return NULL;
    }
    while(courant!=NULL){
        if(plusOcc<courant->donnee.nbOcc){
            plusOcc=courant->donnee.nbOcc;
            resultat=courant;
        }
            courant=courant->suivant;
    }
    return resultat;
}

ListeTQ_DFP intersection(ListeTQ_DFP *l1, ListeTQ_DFP *l2){
    ListeTQ_DFP nouvelle = (ListeTQ_DFP)malloc(sizeof(ListeTQ_DFP));
    ListeDFP courant1=l1->tete;
    while(courant1!=NULL){
        ListeDFP courant2=l2->tete;
        while(courant2!=NULL){
            if(courant1->donnee.fact==courant2->donnee.fact){
                int fact=courant1->donnee.fact;
                int occ=(courant1->donnee.nbOcc<courant2->donnee.nbOcc)?courant1->donnee.nbOcc:courant2->donnee.nbOcc;
                insertion(nouvelle,fact,occ);
            }
            courant2=courant2->suivant;
        }
        courant1=courant1->suivant;
    }
    return nouvelle;
}

ListeTQ_DFP intersectionRe(ListeTQ_DFP *l1, ListeTQ_DFP *l2, ListeTQ_DFP *nouvelle) {
    // 递归终止条件: 如果任一链表为空
    if (l1->tete == NULL || l2->tete == NULL) {
        return *nouvelle;
    }

    ListeDFP curr1 = l1->tete;
    ListeDFP curr2 = l2->tete;

    // 比较当前节点的 fact 值
    if (curr1->donnee.fact == curr2->donnee.fact) {
        int fact = curr1->donnee.fact;
        int occ = (curr1->donnee.nbOcc < curr2->donnee.nbOcc) ? curr1->donnee.nbOcc : curr2->donnee.nbOcc;
        insertion(nouvelle, fact, occ);

        // 递归处理剩余节点
        l1->tete = l1->tete->suivant;
        l2->tete = l2->tete->suivant;
        intersectionRe(l1, l2, nouvelle);
    } else {
        // 如果 fact 值不同, 移动较小的那个链表的指针
        if (curr1->donnee.fact < curr2->donnee.fact) {
            l1->tete = l1->tete->suivant;
        } else {
            l2->tete = l2->tete->suivant;
        }
        intersectionRe(l1, l2, nouvelle);
    }

    return *nouvelle;
}

typedef struct celluleList {
    struct celluleList *suivant;
    ListeTQ_DFP ldfp;
} *ListLL;

void inserList(ListLL *l1, int nombre) {
    // 创建新节点并分配内存
    ListLL nouvelle = (ListLL)malloc(sizeof(struct celluleList));
    if (nouvelle == NULL) {
        // 如果内存分配失败，退出函数
        return;
    }
    nouvelle->ldfp = decomposition(nombre);
    nouvelle->suivant = NULL;

    // 如果链表为空，直接将新节点作为头节点
    if (*l1 == NULL) {
        *l1 = nouvelle;
    } else {
        // 找到链表的最后一个节点
        ListLL courant = *l1;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        // 将新节点插入到链表末尾
        courant->suivant = nouvelle;
    }
}

typedef struct cellule{
    int donnee;
    struct cellule *suivant;
}*ListeEntier;

ListeDFP decomposerEnFacteurs(int nombre, ListeNbre lPre) {
    ListeDFP facteurs = NULL;
    ListeNbre courantPre = lPre;
    int occ;

    while (nombre > 1 && courantPre != NULL) {
        int prime = courantPre->nombre;
        occ = 0;
        
        while (nombre % prime == 0) {
            nombre /= prime;
            occ++;
        }

        if (occ > 0) {
            insertionFacteur(&facteurs, prime, occ);
        }

        courantPre = courantPre->suivant;
        if (courantPre == lPre) break;  // 回到头节点，循环停止
    }

    return facteurs;
}

ListLL construction(ListeEntier lPre, ListeEntier lNbre, ListLL *l1){
     if (lNbre == NULL || lPre == NULL) return;

    ListeEntier courantNbre = lNbre;

    do {
        // 获取当前整数的素数分解
        ListeDFP facteurs = ecomposerEnFacteurs(courantNbre->nombre, lPre);

        // 创建一个新的节点，用于存储该整数的因子列表
        ListLL nouveau = (ListLL)malloc(sizeof(struct celluleList));
        nouveau->ldfp.tete = facteurs;
        nouveau->suivant = *ll;
        *ll = nouveau;

        // 前进到下一个整数节点
        courantNbre = courantNbre->suivant;
    } while (courantNbre != lNbre);  // 如果回到起始节点，停止循环
}

// ListeTQ_DFP calculerPGCD(ListeEntier lNbre) {
//     if (lNbre == NULL) return (ListeTQ_DFP){NULL, NULL};

// }

typedef struct cellule {
    int donnee;
    struct cellule *suivant;
} *ListeCirculaire;

void insererTriee(ListeCirculaire sentinelle, ListeCirculaire nouvelleCellule) {
    ListeCirculaire courant = sentinelle;

    // Trouver la position correcte pour insérer la nouvelle cellule
    while (courant->suivant != sentinelle && courant->suivant->donnee < nouvelleCellule->donnee) {
        courant = courant->suivant;
    }

    // Insérer la nouvelle cellule dans la position trouvée
    nouvelleCellule->suivant = courant->suivant;
    courant->suivant = nouvelleCellule; 
}
