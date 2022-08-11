! Interface to C routine

! MODULE NEINTEROP
!   interface
!     !JF,lat,lon,year,month,day,hour,min,sec,alt,outf
!     subroutine densityprofilefortraninterop(testvar) !bind(C, 'densityProfileFortranInterop_')
!       real, intent(in) :: testvar(2:2)
!       ! Interface blocks don't know about their context,
!       ! so we need to use iso_c_binding to get c_int definition
!       !real, intent(in) :: lat,lon,year,month,day,hour,min,sec,alt(500),outf(1,500)
!       !logical, intent(in) :: JF
!     end subroutine densityprofilefortraninterop
!   end interface
! END MODULE NEINTEROP


MODULE NEINTEROP
  interface
    !JF,
    subroutine densityprofilefortraninterop(lat,lon,year,month,day,hour,min,sec,oput) !bind(C, 'densityProfileFortranInterop_')
      real, intent(in) :: lat
      real, intent(in) :: lon
      real, intent(in) :: year
      real, intent(in) :: month
      real, intent(in) :: day
      real, intent(in) :: hour
      real, intent(in) :: min
      real, intent(in) :: sec
      real, intent(out) :: oput(500)
    end subroutine densityprofilefortraninterop
  end interface
END MODULE NEINTEROP
