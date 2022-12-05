#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);


/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this = NULL;

    this = (LinkedList*) malloc(sizeof(LinkedList));

    if(this != NULL){
    	this->size = 0;
    	this->pFirstNode = NULL;
    }

    return this;
}


/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int size = -1;

    if(this != NULL){
    	size = this->size;
    }

    return size;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* auxNode = NULL;
	int size;

	if(this != NULL){
		size = ll_len(this);

		if(nodeIndex >= 0 && nodeIndex < size){
			auxNode = this->pFirstNode;

			if(auxNode != NULL){// RECORRE HASTA DONDE ESTE EL INDICE DEL NODO Q SE INGRESO
				for(int i = 0; i < nodeIndex; i++){
					auxNode = auxNode->pNextNode;
				}
			}
		}
	}

	return auxNode;
}


/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex, void* pElement)
{
    int returnAux = -1;
	int size;
    Node* newNode = NULL;
    Node* auxNode = NULL;

    if(this != NULL){
    	size = ll_len(this);

    	if(nodeIndex >= 0 && nodeIndex <= size){
    		newNode = (Node*) malloc(sizeof(Node));// CREO ESPACIO EN MEM PARA EL NUEVO NODO

    		if(nodeIndex == 0){
    			newNode->pNextNode = this->pFirstNode; // apunto el nodo nuevo a donde apuntaba la cabezera
    			this->pFirstNode = newNode; // apunto la cabezera al nuevo nodo que agregue
    		}
    		else{
    			auxNode = getNode(this, (nodeIndex - 1));// OBTENGO EL NODO Q SE UBICA EN LA POSICION ANTERIOR A DONDE QUIERE INGRESR UNO NUEVO

    			if(auxNode != NULL){
    				newNode->pNextNode = auxNode->pNextNode; // apunto el nuevo nodo a donde apuntaba el nodo original
    				auxNode->pNextNode = newNode; // apunto el nodo anterior al nuevo nodo creado
    			}
    		}
			newNode->pElement = pElement; // guardo el elemento q se ingreso en el nodo nuevo
			this->size++;

			returnAux = 0;
    	}
    }

    return returnAux;
}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int size;

    if(this != NULL){
    	size = ll_len(this);

    	returnAux = addNode(this, size, pElement);
    }

    return returnAux;
}


/** \brief 2.6 Función ll_get
        Retorna un puntero al elemento que se encuentra en el índice especificado. Verificando que el
		puntero this sea distinto de NULL y que index sea positivo e inferior al tamaño del array. Si la
		verificación falla la función retorna (NULL) y si tiene éxito retorna el elemento.
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* auxNode = NULL;

    if(this != NULL){
		auxNode = getNode(this, index);

		if(auxNode != NULL){
			returnAux = auxNode->pElement;
		}
    }

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    Node* auxNode = NULL;

    if(this != NULL){
		auxNode = getNode(this, index);

		if(auxNode != NULL){
			auxNode->pElement = pElement;
			returnAux = 0;
		}
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 */
int ll_remove(LinkedList* this, int index)
{
    int returnAux = -1;

    Node* nodeToRemove = NULL;
    Node* auxNode = NULL;

    if(this != NULL){
		nodeToRemove = getNode(this, index);

		if(nodeToRemove != NULL){
			if(index == 0){
				this->pFirstNode = nodeToRemove->pNextNode;
			}
			else{
				auxNode = getNode(this, (index-1));

				if(auxNode != NULL){
					auxNode->pNextNode = nodeToRemove->pNextNode;
				}
			}
			this->size--;
			free(nodeToRemove);
			returnAux = 0;
		}
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int size;

    if(this != NULL){
    	size = ll_len(this);

    	for(int i = 0; i < size; i++){
    		ll_remove(this, 0);
    	}

    	returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL){
    	if(ll_clear(this) == 0){
        	free(this);
        	returnAux = 0;
    	}
    }

    return returnAux;
}


/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int size;
    Node* auxNode = NULL;

    if(this != NULL){
    	size = ll_len(this);

    	for(int i = 0; i < size; i++){
    		auxNode = getNode(this, i);

    		if(auxNode != NULL){
    			if(auxNode->pElement == pElement){
    				returnAux = i;
    				break;
    			}
    		}
    	}
    }

    return returnAux;
}


/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    int size;

    if(this != NULL){
    	returnAux = 0;
    	size = ll_len(this);

    	if(size == 0){
    		returnAux = 1;
    	}
    }

    return returnAux;
}


/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this != NULL){
    	returnAux = addNode(this, index, pElement);
    }

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* auxNode = NULL;

    if(this != NULL){
		auxNode = getNode(this, index);

		if(auxNode != NULL){
			returnAux = auxNode->pElement;
			ll_remove(this, index);
		}
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int index;

    if(this != NULL){
    	index = ll_indexOf(this, pElement);
    	returnAux = 0;

    	if(index >= 0){
    		returnAux = 1;
    	}
    }

    return returnAux;
}


/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this, LinkedList* this2)
{
    int returnAux = -1;
    int size;
    int contiene;
    void* auxElement;

    if(this != NULL && this2 != NULL){
    	returnAux = 1;
    	size = ll_len(this2);

    	for(int i = 0; i < size; i++){
    		auxElement = ll_get(this2, i);
    		contiene = ll_contains(this, auxElement);

    		if(contiene == 0){
    			returnAux = 0;
    			break;
    		}
    	}
    }

    return returnAux;
}


/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                                  (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this, int from, int to)
{
    LinkedList* cloneArray = NULL;
    void* auxElement = NULL;
    int size;

    if(this != NULL){
		size = ll_len(this);

    	if(from >= 0 && from < to && to <= size){
        	cloneArray = ll_newLinkedList();

        	if(cloneArray != NULL){
        		for(int i = from; i < to; i++){
        			auxElement = ll_get(this, i);
        			ll_add(cloneArray, auxElement);
        		}
        	}
    	}
    }

    return cloneArray;
}


/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    int size;

    if(this != NULL){
    	cloneArray = ll_newLinkedList();

    	if(cloneArray != NULL){
    		size = ll_len(this);

    		cloneArray = ll_subList(this, 0, size);
    	}
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*, void*), int order)
{
    int returnAux = -1;
    int size;

    void* firstElement = NULL;
    void* secondElement = NULL;
    void* auxElement = NULL;

    if(this != NULL && pFunc != NULL){
    	if(order == 0 || order == 1){
    		size = ll_len(this);

			for(int i = 0; i < size; i++){
				for(int j = i+1; j < size; j++){
					firstElement = ll_get(this, i);
					secondElement = ll_get(this, j);

					if((order == 1 && pFunc(firstElement, secondElement) == 1) || (order == 0 && pFunc(firstElement, secondElement) == -1)){
						auxElement = firstElement;
						ll_set(this, i, secondElement);
						ll_set(this, j, auxElement);
					}
				}
			}

			returnAux = 0;
    	}
    }

    return returnAux;
}




