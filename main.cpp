#include "stdio.h"
#include "stdlib.h"
#include "string"
#include "iostream"
#include "stdbool.h"

class No {
private:
	int id;
	std::string nome;
	float saldo;
	No * prx;
	No * ant;

public:
	No(int id, std::string pNome, float pSaldo) {
		this->id = id;
		this->nome = pNome;
		this->saldo = pSaldo;
		this->prx = NULL;
		this->ant = NULL;
	}

	No * prxNo() {
		return this->prx;
	}

	No * antNo() {
		return this->ant;
	}

	void setPrxNo(No * pProx) {
		this->prx = pProx;
	}

	void setAntNo(No * pAnt) {
		this->ant = pAnt;
	}

	std::string toString() {
		std::string str;
		char number[10];

		sprintf(number, "%.2f", this->saldo);

		str = "id: " + std::to_string(this->id) + "\n" +
			  "Nome: " + this->nome + "\n" +
			  "Saldo: " + number + "\n";
		return str;
	}

	int getId() {
		return this->id;
	}

	std::string getNome() {
		return this->nome;
	}

	void setNome(std::string nome) {
		this->nome = nome;
	}

	void setSaldo(float saldo) {
		this->saldo = saldo;
	}
};

class List {
private:
	No * primeiro;
	No * ultimo;
	int sizeList = 0;
	int id;
public:
	List() {
		id = 0;
		sizeList = 0;
		primeiro = NULL;
		ultimo = NULL;
	}
	
	List(No * no) {
		ultimo = no;
		primeiro = no;
		sizeList = 1;
	}

	~List() {
		delete primeiro;
	}

	int size() {
		return sizeList;
	}

	bool vazia() {
		return sizeList == 0;
	}

	bool append(std::string nome, float saldo) {
		No * no = new No(++id, nome, saldo);
		
		No * tmp;
		
		if (vazia()) {
			primeiro = no;
			ultimo = no;
			this->sizeList += 1;
			return true;
		}
		else {
			ultimo->setPrxNo(no);
			tmp = ultimo;
			ultimo = no;
			ultimo->setAntNo(tmp);
			this->sizeList += 1;
			return true;
		}
		return false;
	}

	void mostra() {
		if (vazia()) {
			std::cout << "Lista valia" << std::endl;
			return;
		}
		No * tmp;
		tmp = primeiro;
		while (tmp != NULL) {
			std::cout << tmp->toString() << "--------------------------\n";
			tmp = tmp->prxNo();
		}
	}

	No * selectCliente(int id) {
		No * tmp;
		tmp = primeiro;
		if (!vazia()) {
			while (tmp != NULL) {
				if (tmp->getId() == id) {
					return tmp;
				}
				tmp = tmp->prxNo();
			}
		}
		return NULL;
	}

	No * selectCliente(std::string nome) {
		No * tmp;
		tmp = primeiro;
		if (!vazia()) {
			while (tmp != NULL) {
				if (tmp->getNome() == nome) {
					return tmp;
				}
				tmp = tmp->prxNo();
			}
		}
		return NULL;
	}

	bool updateCliente(int id, std::string newNome) {
		No * tmp = selectCliente(id);
		if (tmp != NULL) {
			tmp->setNome(newNome);
			return true;
		}
		return false;
	}

	bool updateCliente(int id, float saldo) {
		No * tmp = selectCliente(id);
		if (tmp != NULL) {
			tmp->setSaldo(saldo);
			return true;
		}
		return false;
	}

	bool updateCliente(std::string newNome, float saldo) {
		No * tmp = selectCliente(newNome);
		if (tmp != NULL) {
			tmp->setSaldo(saldo);
			return true;
		}
		return false;
	}

	bool pop() {
		if (!vazia()) {
			No * tmp = ultimo;
			if (ultimo == primeiro) {
				ultimo = NULL;
				primeiro = NULL;
				this->sizeList -= 1;
			}
			else {
				ultimo = tmp->antNo();
				tmp->antNo()->setPrxNo(NULL);
				this->sizeList -= 1;
			}
			free(tmp);
			return true;
		}
		else {
			return false;
		}
	}

	void clear() {
		while (this->pop()) {
			continue;
		}
	}

	bool deleteCliente(int id) {
		No * tmp = selectCliente(id);
		if (tmp != NULL) {
			tmp->antNo()->setPrxNo(tmp->prxNo());
			tmp->prxNo()->setAntNo(tmp->antNo());
			free(tmp);
			this->sizeList -= 1;
			return true;
		}
		return false;
	}
};

int main(){
	List ls;

	if (!ls.append("Cliente 1", 800) || !ls.append("Cliente 2", 700) || !ls.append("Cliente 3", 350)) {
		printf("Erro ao inserir cliente\n");
	};
	ls.mostra();
	if (!ls.updateCliente(1,"Cliente [1]") || !ls.updateCliente("Cliente 2", 300)) {
		printf("Cliente nao encontrado\n");
	}
	ls.mostra();
	if (!ls.deleteCliente(2)) {
		printf("Cliente nao encontrado\n");
	}
	ls.clear();
	return 0;
}
