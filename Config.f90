      subroutine config(gm,tinf,r,vinf,ainf) bind(c,name='nml_config')

       use,intrinsic :: iso_c_binding,only:c_double,c_int,c_char
       implicit none

       real(kind=c_double), intent(inout) :: gm
       real(kind=c_double), intent(inout) :: tinf
       real(kind=c_double), intent(inout) :: r
       real(kind=c_double), intent(inout) :: vinf
       real(kind=c_double), intent(inout) :: ainf

       namelist /gasprop/ gm, tinf, r, vinf, ainf

       open(unit=100,file='lsi_config.nml',status='old')
       write(*,*) 'Reading gasprop from lsi_config.nml'
       read(unit=100,nml=gasprop)
       close(unit=100)

      end subroutine config
