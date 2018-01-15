! Copyright (c) 2015 Alberto Otero de la Roza <aoterodelaroza@gmail.com>,
! Ángel Martín Pendás <angel@fluor.quimica.uniovi.es> and Víctor Luaña
! <victor@fluor.quimica.uniovi.es>. 
!
! critic2 is free software: you can redistribute it and/or modify
! it under the terms of the GNU General Public License as published by
! the Free Software Foundation, either version 3 of the License, or (at
! your option) any later version.
! 
! critic2 is distributed in the hope that it will be useful,
! but WITHOUT ANY WARRANTY; without even the implied warranty of
! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
! GNU General Public License for more details.
! 
! You should have received a copy of the GNU General Public License
! along with this program.  If not, see <http://www.gnu.org/licenses/>.

! This module contains code for the Yu and Trinkle Bader integration-on-a-grid.
! See:
!    Min Yu, Dallas Trinkle, J. Chem. Phys. 134 (2011) 064111.
! for details on the algorithm.
module yt
  use systemmod, only: system
  implicit none

  private

  public :: yt_integrate
  public :: yt_weights
  public :: ytdata_clean
  public :: ytdata

  !> Data needed to regenerate the YT weights for a given attractor.
  type ytdata
     integer :: nbasin !< Number of basins
     integer :: nn !< Number of grid points
     integer :: nvec !< Number of WS vectors
     integer, allocatable :: nlo(:) !< Number of points with lower density
     integer, allocatable :: ibasin(:) !< Basin identifier for interior points
     integer, allocatable :: iio(:) !< Density sorting map 
     integer, allocatable :: inear(:,:) !< Identifiers for neighbor points
     real*8, allocatable :: fnear(:,:) !< Flux to neighbor
  end type ytdata
  
  interface
     module subroutine yt_integrate(s,ff,discexpr,atexist,ratom,nbasin,xcoord,idg,luw)
       type(system), intent(inout) :: s
       real*8, intent(in) :: ff(:,:,:)
       character*(*), intent(in) :: discexpr
       logical, intent(in) :: atexist
       real*8, intent(in) :: ratom
       integer, intent(out) :: nbasin
       real*8, allocatable, intent(inout) :: xcoord(:,:)
       integer, allocatable, intent(inout) :: idg(:,:,:)
       integer, intent(out) :: luw
     end subroutine yt_integrate
     module subroutine yt_weights(luw,din,idb,w,dout)
       integer, intent(in), optional :: luw
       type(ytdata), intent(in), optional :: din
       integer, intent(in), optional :: idb
       type(ytdata), intent(inout), optional :: dout
       real*8, intent(inout), optional :: w(:,:,:)
     end subroutine yt_weights
     module subroutine ytdata_clean(dat)
       type(ytdata), intent(inout) :: dat
     end subroutine ytdata_clean
  end interface

end module yt
