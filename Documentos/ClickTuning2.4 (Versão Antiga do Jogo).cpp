//JOGNA2 - GRUPO 6

#include<stdio.h>
#include<iostream>
#include<graphics.h>
#include <time.h>

#define CR	13

struct fase{
	long long int pos, comprimento;
};

struct carro1{
	long long int pos, velocidade, aceleracao, velocidadeMax;
};

struct carromaquina{
	long long int pos, velocidade, aceleracao, velocidadeMax;
};

carro1 jogador;
fase fase1;
carromaquina oponente;
int velocidade, tamX, tamY, FPS, tam, gold;
int FaseAtual, LimiteFase;
void *R;
int pg = 1;
unsigned long long gt1, gt2;
bool result;


bool fase(int comprimento){
	bool resultado;
	
	jogador.aceleracao = 5;
	oponente.aceleracao = 0;
	oponente.pos =0;
	oponente.velocidade = 0;
	
	while (jogador.pos <= comprimento){
		
		printf("Funcao fase\n");
		/*gt2 = GetTickCount();
		gt1 = gt2;
		if (gt2 - gt1 > 1000/FPS){
			gt2 = gt1;*/
			
			if(pg == 1) pg = 2; else pg = 1;
			setactivepage(pg);
			gt1 = GetTickCount();
			setbkcolor(RGB(0,0,0));
			cleardevice();
		
			//Movimentação do jogador
			//jogador.velocidade = 0;
			if(jogador.velocidadeMax >= jogador.velocidade){
			
				if(GetAsyncKeyState('W')&0x0080) {
					jogador.velocidade += jogador.aceleracao;
					printf("suhaush");
				}
			      	
			    else if(GetAsyncKeyState(VK_SPACE)&0x0080)
			      	jogador.velocidade += jogador.aceleracao*5;
			    else if(GetAsyncKeyState(VK_LEFT)&0x0080)
			      	jogador.velocidade -= jogador.aceleracao*5;
			}

		      	
		    jogador.pos += jogador.velocidade;
			fase1.pos -= jogador.velocidade;
			
			if(oponente.velocidade <= oponente.velocidadeMax){
				oponente.velocidade += oponente.aceleracao;
			}
			oponente.pos += oponente.velocidade;
			printf("%d", oponente.pos);
					
			//Desenhar a fase
			putimage(fase1.pos, 0, R, COPY_PUT);
			putimage(fase1.pos-tamX, 0, R, COPY_PUT);
			putimage(fase1.pos+tamX, 0, R, COPY_PUT);
			if(fase1.pos <= -tamX || fase1.pos >= tamX ){
				fase1.pos = 0;	
			}
			
			setfillstyle(1,RGB(255,255,0));
			bar(50,50,100,100);
			setfillstyle(1,RGB(0,255,0));
			bar(oponente.pos,100,oponente.pos+50,150);
			setvisualpage(pg);
			do{
				gt2 = GetTickCount();
			}while(gt2 - gt1 > 1000/FPS);
			
	}
	if (jogador.pos >= comprimento && oponente.pos < comprimento){ //Ganhou
		resultado = true;
	}
	else if ((jogador.pos < comprimento && oponente.pos >= comprimento) || (jogador.pos = comprimento && oponente.pos >= comprimento )){ //Perdeu
		resultado = false;
	}

	
	return(resultado);
}

int main(){
	
	jogador.pos = 0;
	fase1.comprimento = 15000;
	tamX = 1000;
	tamY = 600;
	
	initwindow(tamX,tamY,"Click Tuning",50,50);
	
	char tecla;
	
	FaseAtual = 0;
	gold = 0;
	tecla = 0;
	velocidade = 0;
	FPS = 60;
	tam = imagesize(0,0,1000,600);
	R = malloc(tam);
	
	fase1.pos = 0;
	
	readimagefile("PaginaPrincipal2.bmp",0,0,1000,600);
	getimage(0, 0, 1000, 600, R);
	cleardevice();
	while(tecla != CR) {
		printf("Entrei\n");
		if(FaseAtual == 0){
			oponente.velocidadeMax = 10;
			jogador.velocidadeMax = 100;
			printf("Aqui\n");
			result = fase(1500000);
			if (result){
				FaseAtual = 1;
				gold += 100;
			}
			else {
				FaseAtual = 0;
				gold += 50;
			}	
		}
			
		if(FaseAtual == 1){
			oponente.velocidadeMax = 50;
			jogador.velocidadeMax = 100;
			result = fase(10000);
			if (result){
				FaseAtual = 2;
				gold += 100;
			}
			else {
				FaseAtual = 1;
				gold += 50;
			}	
		}
			
		if(FaseAtual == 2){
			oponente.velocidadeMax = 75;
			jogador.velocidadeMax = 100;
			result = fase(15000);
			if (result){
				FaseAtual = 3;
				gold += 100;
			}
			else {
				FaseAtual = 2;
				gold += 50;
			}	
		}
			
		if(FaseAtual == 3){
			oponente.velocidadeMax = 95;
			jogador.velocidadeMax = 100;
			if (fase(15000)){
				FaseAtual = 4;
				gold += 400;
			}
			else {
				FaseAtual = 3;
				gold += 50;
			}	
		}
			
		printf("%d\n", jogador.pos);
				
		/*if(jogador.pos > fase1.comprimento){
			printf("Voce ganhou\n");
		}*/
			
		//delay(50);
			
		setvisualpage(pg);
			
		fflush(stdin);
		if (kbhit())
			tecla = getch ();
	
	}
	closegraph();
	return (0);
	
}
