#include <iostream>
#include <list>
#include <climits>  //biblioteca para usar o valor máximo (INT_max)
using namespace std;

struct no  //struct que axilia a guardar os vertices do grafo
{
	int v; // vertice adjacente
	int peso; // peso da aresta
};

void cria_aresta(list<no>adj[], int u, int v, int p, int orientado)
{
	//função responsável por determinar as arestas do grafo
	//declaração de variáveis
	no aux;  //var aux

	//criando as arestas
	aux.peso = p;
	aux.v = v;
	adj[u].push_back(aux);  //criação das fila
	if(orientado == 0)  //não orientado
	{
		//fazendo a volta do vetor
		aux.v = u;
		adj[v].push_back(aux);
	}
}

void dijkstra(list<no>adj[], int nVertices, int start, int end)
{
	/*
	-> FUNÇÃO RESPONSÁVEL POR DEFINIR O MENOR CAMINHO ENTRE DOIS VERTICES A PARTIR
	DAS INFORMAÇÕES DADAS (pesos das arestas e se são orientadas ou não)
	-> TAMBÉM DEFINE O CUSTO DO CAMINHO PERCORRIDO (sendo assim, o caminho que ele definir
	terá o menor custo entre dois vertices)
	*/
	bool intree[50];  //dirá se o vertice já foi ou não adicionado na arvore geradora minima
	int u;  //var aux
	int distance[50];  //vetor que guarda a distância de um vertice a outro
	int parent[50];  //pai - de onde um vetor se origina ao ser descoberto
	/* quando o pai for igual a -1 para determinado vertice quer dizer
	que o mesmo não possui um pai, ou seja, o vertice ainda não foi
	descoberto e por isso não possui "origem"*/
	int v;  //var aux
	int destino;  //var aux para avaliar o destino
	int weight;  //var auxiliar para avaliar o peso
	int dist;  //var aux para ajudar a encontrar
	list<no> :: iterator p;  /*interator auxiliar para varrer a lista de adjacência
							 de um vertice*/
	list<int> caminho;  //fila auxiliar para mostrar o menor caminho

	//inicialização inicial do código
	for(u = 0; u < nVertices; u++)
	{
		intree[u] = false;  //nenhum vertice adicionado na arvore minima
		distance[u] = INT_MAX;  //distância de todos como infinito até descobrir uma distância ideal0
		parent[u] = -1;  //marcando os vertices como sem origem
	}
	distance[start] = 0;  //distância do vertice inicial como 0
	v = start;  //definir um vertice parâmetro

	//aqui começa a varrer as arrestas em busca de um caminho com o menor custo
	while(intree[v] == false)
	{
		intree[v] = true;  //vertice parâmetro adicionado na lista
		for(p = adj[v].begin(); p != adj[v].end(); p++)
		{
			destino = p->v;
			weight = p->peso;
			if(distance[destino] > distance[v] + weight)
			{
				/*caso seja percebido um caminho e o vertice ainda não foi adicionado
				na lista como um caminho alternativo (menor) ele é adicinado agora*/
				distance[destino] = distance[v] + weight;
				parent[destino] = v;
			}
		}
		v = 0;
		dist = INT_MAX;  //definição de distância parâmetro
		for(u = 0; u < nVertices; u++)
		{
			if(intree[u] == false && dist > distance[u])
			{
				dist = distance[u];  //distância mais curta encontrada
				v = u;  //redefinição do vertice parâmetro
			}
		}
	}

	/*aqui ocorre a varredura dos vertices para fazer a determinação do menor
	caminho percorrido*/
	caminho.push_front(end);  //criando uma fila com inicio no vertice de destino
	u = parent[end];
	while(u != start)  //o while para quando o caminho chegar no vertice de incio
	{
		caminho.push_front(u);
		u = parent[u];
	}
	caminho.push_front(u);

	//saida do menor caminho entre os vertices start e end
	cout << "Menor caminho desse passageiro: ";
	while(!caminho.empty())  //varrendo a lista auxiliar
	{
		u = *caminho.begin();
		cout << u << " ";  //saida do vertice do caminho
		caminho.pop_front();  //"limpando" a lista
	}
	cout << endl;

	//saida do menor custo entre os vertices
	cout << "Tempo em minutos: " << distance[end] << endl;
	/*distance[end] é o custo feito para chegar até o vertice de destino, sendo
	esse o menor caminho, tem também o menor custo*/
}

void caminho_chamada1(list<no>adj[], int nVertices, int &i, int &final)   // chama a funcao de menor caminho dos proximos passageiros
{
	// declaracao de var
	int end;  // ponto de fim(destino do passageiro)

	i++;  // incremento da quantidade de passageiros

	// entrada do vertice de inicio e final
	cout << "ENTRE COM O VERTICE FINAL DO CAMINHO DO PASSAGEIRO " << i << ":" << endl;
	cin >> end;
	dijkstra(adj, nVertices, final, end);	
	
	// mudando o vertice final
	final = end;
	
}

int caminho_chamada(list<no>adj[], int nVertices, int &i)   // chama a funcao de menor caminho do primeiro passageiro
{
	// declaracao de var
	int end;  // ponto de fim(destino do passageiro)
	int start;  // ponto de começo(incio do passageiro)

	i++;  // incremento da quantidade de passageiros

	// entrada do vertice de inicio e final
	cout << "ENTRE COM OS VERTICES INICIAL E FINAL DO CAMINHO DO PASSAGEIRO " << i << ":" << endl;
	cin >> start >> end;
	dijkstra(adj, nVertices, start, end);
	
	// retorno do ponto final do primeiro passageiro
	return end;

}

int main()
{
	//declaração de variáveis
	int nVertices;  //quantidade de vertices do grafo
	int orientado;  // 0 -> não orientado	1 -> orientado
	int u;  //vertice de origem da aresta
	int v;  //vertice de destino da aresta
	int p;  //peso da aresta
	list<no> adj[100];  //lista de adjacência
	int i = 0;  // numeracao do passageiro
	int final;  // final da corrida anterior

	orientado = 0;
	/*
	-> será usado o orientado = 0 porque o motorista podera ir e
	voltar de um ponto dentro da regiao ativida dele de funcionamento
	*/

	//entrada dos dados iniciais (Número de vertices)
	cout << "QUANTIDADE DE PONTOS: " << endl;
	cin >> nVertices;

	//entrada do vertice de origem e destino e o peso de sua aresta
	cout << "CAMINHOS (INICIO, FIM e PESO DO CAMINHO): " << endl;
	cin >> u >> v >> p;
	while((u != -1) && (v != -1) && (p != -1))  //condição de parada de entrada de dados
	{
		//criação das arestas (função CRIA ARESTA)
		cria_aresta(adj, u, v, p, orientado);
		cin >> u >> v >> p;
	}

	// chamada de funcao do primeiro passageiro
	final = caminho_chamada(adj, nVertices, i);

	// INCIO DA CHAMADA DE MAIS PASSAGEIROS NA VIAGEM
	int pergunta = 1;  /*
						1 -> SIM
						0 -> NAO
						*/

	while(pergunta != 0) //estruturade repetição para verificação se há mais passageiros ou não
	{
		cout << "TEM MAIS CORRIDA? (1->SIM e 0->NAO)" << endl;
		cin >> pergunta;
		switch(pergunta)
		{
		case 1: //caso haja mais passageiros será chamada a função para os próximos
			caminho_chamada1(adj, nVertices, i, final);
			break;
		default:
			pergunta = 0;
			break;
		}
	}
	return 0;
}
