	program run_qfs

	implicit none

	real*8 Ebeam,P,theta,th
	real*8 pfermi,eps,epsd  !fermi momentum,nucleon sep. NRG,Delta sep. NRG
	real*8 ztarg, atarg
	real*8 sigma
	real*8 degrad !degrees to radians

	parameter(degrad=0.017453292)

	pfermi = 0.0d0
	eps = 0.0d0
	epsd = 0.0d0
	ztarg = 1.0d0
	atarg = 1.0d0

	write(6,*) 'Enter beam energy (MeV)'
	read(5,*) Ebeam

	write(6,*) 'Scattered particle momentum (MeV)'
	read(5,*) P

	write(6,*) 'Scattering angle (in degrees)'
	read(5,*) theta
	th = theta*degrad

	
	write(6,*) 'NOTE: I am assuming a hydrogen target.'
	write(6,*) 'If you want something else, learn some fortran.'

	call qfsv(ebeam,p,th,pfermi,eps,epsd,ztarg,atarg,sigma)

	write(6,*) 'XSEC is',sigma
	
	end
