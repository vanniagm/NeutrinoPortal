/*====== Modules ===============
   Keys to switch on 
   various modules of micrOMEGAs  
================================*/
      

#define OMEGA      
#define CDM_NUCLEON      
#define NEUTRINO
#define DECAYS
  /* Calculate relic density and display contribution of  individual channels */

#define CLEAN  to clean intermediate files

#define PI 3.14159265

/*===== End of DEFINE  settings ===== */


#include"../sources/micromegas.h"
#include"../sources/micromegas_aux.h"
#include"lib/pmodel.h"





int main(int argc,char** argv)
{  int err,i,j,k,l,jj;
   char cdmName[10];
   char *maj="maj", *Mdm="Mdm", *kk="kk",*Lx="Lx";
   char *zm1="zm1", *zm2="zm2", *zm3="zm3" ,*Lam="Lam";
   char *mudm1="mudm1",*mudm2="mudm2",*mudm3="mudm3" ;
   char *Un1x1="Un1x1", *Un1x2="Un1x2",*Un1x3="Un1x3";
   char *Un2x1="Un2x1", *Un2x2="Un2x2", *Un2x3="Un2x3";
   char *Un3x1="Un3x1", *Un3x2="Un3x2", *Un3x3="Un3x3";
   char *En1x1="En1x1", *En1x2="En1x2", *En1x3="En1x3";
   char *En2x1="En2x1", *En2x2="En2x2", *En2x3="En2x3";
   char *En3x1="En3x1", *En3x2="En3x2", *En3x3="En3x3";
   double mfe, kn, zz, muDM, lambda, lh;
   double zd[3],mmu[3],DeltaSQ[3][3];
   double UNN[3][3], ENN[3][3],UNUN[3];
   double ten12,ten23,ten13;/*tun12,tun23,tun13*/
   double MNS[3][3],MNSERR[3][3],trdeltasq;
   double deltasq0,deltasq2,deltasqsum;
   int spin2, charge3,cdim;
   int IN,JN,KN,LN,JJN;
   double Omegah2Planck,Omegah2PlanckE;
   double XSMAX,XSMIN,LamMAX,pbcm2;
   int fast=1;
   double Beps=1.E-5, cut=0.01;
   double Omega,Xf;  
   double pA0[2],pA5[2],nA0[2],nA5[2],sigtot;
   double Nmass=0.939,Nmass2=122.,Nmassp=.938; /*nucleon mass*/
   double SCcoeff,SCcoeff2,SCcoeffp; 
   double nu[NZ], nu_bar[NZ],mu[NZ];
   double Ntot,Nutot,Muontot;
   int forSun=1;
   int count,INDEX;
   double Emin=1;
   char fname[100];
   double width1,width2,brf;
   char * pname1, * pname2;
   FILE * mpsi;


    
    if (argc > 1)
    {
	  printf("argv[%d] = %s\n", argc-1, argv[1]);
    }
  else
    {
      printf(" Correct usage:  ./main  <INDEX OF FILE FOR EACH FERMION MASS> \n");
      printf("Example: ./main 1 \n");
      exit(1);
    }
    
                               
INDEX=atoi(argv[1]);
 
	  if(INDEX<0||INDEX>200){ exit(1);}
	  printf("INDEX %i\n",INDEX);
/* build the current file name */

         snprintf(fname,100, "mpsi.%i.dat",INDEX);
	  
  mpsi=fopen (fname,"w");
 /*  mpsi = fopen ("mpsi.text","w");*/
   
   if ((mpsi= fopen(fname, "w")) == NULL) {
   printf("failed to open %s\n", fname);
    exit(1);
     }
   	  
   mfe=INDEX*1.E0;
   assignValW(Mdm, mfe);
  
  ForceUG=0;  /* to Force Unitary Gauge assign 1 */

	ENN[0][0]=0.;
  	ENN[0][1]=0.;
   	ENN[0][2]=1.;
   	ENN[1][0]=0.;
   	ENN[1][1]=1.;
   	ENN[1][2]=0.;
   	ENN[2][0]=1.;
   	ENN[2][1]=0.;
   	ENN[2][2]=0.;
   	
   	assignValW(En1x1,ENN[0][0]);
   	assignValW(En1x2,ENN[0][1]);
   	assignValW(En1x3,ENN[0][2]);
   	assignValW(En2x1,ENN[1][0]);
   	assignValW(En2x2,ENN[1][1]);
   	assignValW(En2x3,ENN[1][2]);
   	assignValW(En3x1,ENN[2][0]);
   	assignValW(En3x2,ENN[2][1]);
   	assignValW(En3x3,ENN[2][2]);
   

			    zd[0]=0.;    
			    assignValW(zm1,zd[0]);   
			    
		            zd[1]=0.;
		            assignValW(zm2,zd[1]); 
			     zd[2]=2.;    
			     assignValW(zm3,zd[2]);



/* Relic abundance constraints */
	  Omegah2Planck  = 0.1198;
	  Omegah2PlanckE = 0.0026;

/* PMNS Matrix angles */
 
   MNS[0][0]=.828;
   MNS[0][1]=.547;
   MNS[0][2]=.148;
   MNS[1][0]=.371;
   MNS[1][1]=.57;
   MNS[1][2]=.704;
   MNS[2][0]=.388;
   MNS[2][1]=.589;
   MNS[2][2]=.683;
   MNSERR[0][0]=.0073;
   MNSERR[0][1]=.011;
   MNSERR[0][2]=.0035;
   MNSERR[1][0]=.0487;
   MNSERR[1][1]=.043;
   MNSERR[1][2]=.0298;
   MNSERR[2][0]=.0471;
   MNSERR[2][1]=.0413;
   MNSERR[2][2]=.031;
   
   deltasqsum=.014;  /*Z decay constraint 3 sigma*/

   
   /*Neutrino Physics */
   
   /*UNUN[1]=UNN[1][1]-(1./2.)*UNN[1][1]*(mmu[1]/Lam)^2;
   UNUN[2]=UNN[2][2]-(1./2.)*UNN[2][2]*(mmu[2]/Lam)^2;
   UNUN[3]=UNN[3][3]-(1./2.)*UNN[3][3]*(mmu[3]/Lam)^2;*/
   
   /*Fixing to Maximum values for deltasq-> Max mu[1] and mu[2] given by lepton decays*/
   assignValW(maj, 1.E-9);
   
  
   
   
   UNN[0][0]=MNS[0][0]; /*cos(tun12)*cos(tun13);*/
   UNN[0][1]=MNS[0][1]; /*sin(tun12)*cos(tun13);*/
   UNN[0][2]=MNS[0][2]; /*sin(tun13);*/
   UNN[1][0]=MNS[1][0];/*-sin(tun12)*cos(tun23)-cos(tun23)*sin(tun23)*sin(tun13);*/
   UNN[1][1]=MNS[1][1];/*cos(tun12)*cos(tun23)-sin(tun12)*sin(tun23)*sin(tun13);*/
   UNN[1][2]=MNS[1][2];/*sin(tun23)*cos(tun13);*/
   UNN[2][0]=MNS[2][0];/*sin(tun12)*sin(tun23)-cos(tun12)*cos(tun23)*sin(tun13);*/
   UNN[2][1]=MNS[2][1];/*-cos(tun12)*sin(tun23)-sin(tun12)*cos(tun23)*sin(tun13);*/
   UNN[2][2]=MNS[2][2];/*cos(tun23)*cos(tun13)*/
   
   assignValW(Un1x1,UNN[0][0]);
   assignValW(Un1x2,UNN[0][1]);
   assignValW(Un1x3,UNN[0][2]);
   assignValW(Un2x1,UNN[1][0]);
   assignValW(Un2x2,UNN[1][1]);
   assignValW(Un2x3,UNN[1][2]);
   assignValW(Un3x1,UNN[2][0]);
   assignValW(Un3x2,UNN[2][1]);
   assignValW(Un3x3,UNN[2][2]);
   
   
   mmu[1]=0; /*GeV*/
   assignValW(mudm2,mmu[1]);
   
   pbcm2 = 1.E-36;
   IN=45.;/*25;*/
   JN=35.;/*25*;*/
   JJN=15.;/*20;*/
   KN=5.;/*10;*/
   LN=10.;/*15;*/



   for(i=0;i<IN;i++)
   {
   lambda=i*9000./(IN-1.)+1000.; /*Minimum 1000 GeV*/
   assignValW(Lam,lambda);
   
   
   for(jj=0;jj<JJN;jj++)
   {
   mmu[0]=jj*38./(JJN-1.)+80.; /*Max 117 GeV*/
   assignValW(mudm1,mmu[0]); 
   
   for(j=0;j<JN;j++)
   {
   mmu[2]=j*117./(JN-1.)+1.; /*Max 117 GeV*/
 
    assignValW(mudm3,mmu[2]);
    
   /* deltasq0=pow((mmu[0]/lambda),2.);
    deltasq2=pow((mmu[2]/lambda),2.);
   
   if (deltasq0<=deltasqsum && deltasq2<= deltasqsum){/*
   
   /*generate random angle: (rand() % 360)*PI/180;*/
   
    /*trdeltasq= pow(mmu[1]/lambda,2+pow(mmu[2]/lambda,2+pow(mmu[3]/lambda,2  */
    
  /* for(f2=1;f2=3;f2++){DeltaSQ[0][0] +=MNS[0][f2]*pow(mmu[f2]/lambda,2.)*MNS[0][f2];}
   for(f2=1;f2=3;f2++){DeltaSQ[0][1] +=MNS[0][f2]*pow(mmu[f2]/lambda,2.)*MNS[1][f2];}
   for(f2=1;f2=3;f2++){DeltaSQ[0][2] +=MNS[0][f2]*pow(mmu[f2]/lambda,2.)*MNS[2][f2];}
   for(f2=1;f2=3;f2++){DeltaSQ[1][0] +=MNS[1][f2]*pow(mmu[f2]/lambda,2.)*MNS[0][f2];}
   for(f2=1;f2=3;f2++){DeltaSQ[1][1] +=MNS[1][f2]*pow(mmu[f2]/lambda,2.)*MNS[1][f2];}
   for(f2=1;f2=3;f2++){DeltaSQ[1][2] +=MNS[1][f2]*pow(mmu[f2]/lambda,2.)*MNS[2][f2];}
   for(f2=1;f2=3;f2++){DeltaSQ[2][0] +=MNS[2][f2]*pow(mmu[f2]/lambda,2.)*MNS[0][f2];}
   for(f2=1;f2=3;f2++){DeltaSQ[2][1] +=MNS[2][f2]*pow(mmu[f2]/lambda,2.)*MNS[1][f2];}
   for(f2=1;f2=3;f2++){DeltaSQ[2][2] +=MNS[2][f2]*pow(mmu[f2]/lambda,2.)*MNS[2][f2];}*/
   
      
   
	   for(k=0;k<KN;k++)
	   {

	    lh=k*1.2/(KN-1.)-.6;
	   assignValW(Lx,lh);

	   
			   for(l=0;l<LN;l++)
			{
			    kn=l*3./(LN-1.)+1.;
			   assignValW(kk,kn);   
			   
			   
			  		  
/*-----------------------------------MicrOmegas functions---------------------------------------------------*/
						  err=sortOddParticles(cdmName);
						if(err) { printf("Can't calculate %s\n",cdmName); return 1;}		  
						   qNumbers(cdmName, &spin2, &charge3, &cdim);
					     
						#ifdef OMEGA
						// to exclude processes with virtual W/Z in DM   annihilation      
						  VZdecay=0; VWdecay=0; cleanDecayTable();
						  Omega=darkOmega(&Xf,fast,Beps);				  
						#endif
				/*ABUNDANCE CONSTRAINT **/
			if (Omegah2Planck-3.*Omegah2PlanckE<=Omega&& Omega<= Omegah2Planck+3.*Omegah2PlanckE)
				{
						#ifdef CDM_NUCLEON        
					nucleonAmplitudes(CDM1,NULL, pA0,pA5,nA0,nA5);
					 SCcoeff=4/M_PI*3.8937966E8*pow(Nmass*Mcdm/(Nmass+ Mcdm),2.)*pbcm2;
				      sigtot=SCcoeff*pow(54.*pA0[0]+(131.-54.)*nA0[0],2.)/pow(131.,2.);				  
					#endif
					#ifdef NEUTRINO	  
					  err=neutrinoFlux(Maxwell,forSun, nu,nu_bar);
				  spectrInfo(Emin/Mcdm,nu_bar, &Nutot,NULL);							  
						/* Upward events */				  
						  muonUpward(nu,nu_bar, mu);
						    spectrInfo(Emin/Mcdm,mu, &Ntot,NULL);   
						  muonContained(nu,nu_bar,1., mu);
		  			        spectrInfo(Emin/Mcdm,mu, &Muontot,NULL);      
						#endif
						#ifdef DECAYS
						txtList LZ,Lh;
							   
						   pname1=pdg2name(23); 
						  width1=pWidth(pname1,&LZ);
		   				   pname2=pdg2name(25);
						   width2=pWidth(pname2,&Lh);
						   brf=findBr(Lh,"~Psi,~Psi-");
						   
						#endif
				
						   fprintf(mpsi,"%.3E ",mfe);
						   fprintf(mpsi,"%.3E ",lambda);
						   fprintf(mpsi,"%.3E ",mmu[0]);
						   fprintf(mpsi,"%.3E ",mmu[2]);
						   fprintf(mpsi,"%.3E ",lh);
						   fprintf(mpsi,"%.3E ",kn);
						   fprintf(mpsi,"%.4E ",Omega);
						   fprintf(mpsi," %.4E %.4E %.4E ",
						       SCcoeff*pow(nA0[0],2.),SCcoeff*pA0[0]*pA0[0],sigtot);
						   fprintf(mpsi," %.4E ",Nutot); /*nu flux*/
						   fprintf(mpsi," %.4E ",Ntot); /*muon flux*/
						   fprintf(mpsi," %.4E ",Muontot); /*Muon contained*/  
						   fprintf(mpsi," %.4E ",width1); /*Z width */
						   fprintf(mpsi," %.4E ",width2); /*H width*/	
						   fprintf(mpsi," %.3E \n",brf);/*H BrF*/
						   
						   				    
						#ifdef CLEAN
						#endif
					}  
					/*else
					{ printf("No agreement in line %i,%i,%i,%i,%i\n",i,j,jj,k,l);} */              
                           /*{ if deltasq*/
		     	 } /*k */
	   } /* lx*/
   }/* mu[3] loop*/
   }/* mu[1] loop*/
   }/*lambda loop*/
  return 0;
}
