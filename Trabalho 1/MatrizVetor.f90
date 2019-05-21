module matrix_vector_product

    ! isso é basicamente um outro arquivo f90 com funções dentro;
    ! se ajudar, uma "classe" com funções.
    
        integer :: i, j
    contains
    
    ! contém funções de criação de matriz, vetores,
    ! e as funções de produto matriz-vetor:
    !	1) Pela coluna;
    !	2) Pela linha.
    
        function matrix(n)
            integer, intent(in) :: n
            double precision :: matrix(n,n)
            call random_number(matrix)
            matrix = matrix*100
        end function matrix
    
        function vector(n)
            integer, intent(in) :: n
            double precision :: vector(n)
            call random_number(vector)
            vector = vector*100
        end function vector
    
        function prodCol(matrix, vector, n, time)
            double precision, intent(in) :: matrix(n,n), vector(n)
            real, intent(out) :: time
            integer :: start, finish
            double precision :: prodCol(n)
            prodCol(:) = 0
    
            call system_clock(start)
            do j = 1,n
                prodCol(:) = prodCol(:) + matrix(:,j) * vector(j)
            end do
            call system_clock(finish)
            time = finish - start
        
        end function prodCol
    
        function prodRow(matrix, vector, n, time)
            double precision, intent(in) :: matrix(n,n), vector(n)
            double precision :: prodRow(n)
            real, intent(out) :: time
            integer :: start, finish
            prodRow(:) = 0
            
            call system_clock(start)
            do j = 1,n
                prodRow(j) = SUM(matrix(j,:) * vector(:))
            end do
            call system_clock(finish)
            time = finish - start
    
        end function prodRow
    
    end module matrix_vector_product
    
    program MatrizVetor
    
    ! 1° tempo: Produto mantendo linha
    ! 2° tempo: Produto mantendo coluna
    
        use matrix_vector_product
        implicit none
        integer, parameter, dimension(100) :: n = [(i, i = 100,10000,100)]
        integer, parameter :: final = size(n)
        real :: timeRow, timeCol
        double precision :: M(n(final),n(final)), v(n(final)), resultRow(n(final)), resultCol(n(final))
        
        M = matrix(n(final))
        v = vector(n(final))
        
        do i = 1,final
            resultCol = prodCol(M,v,n(i),timeCol)
            write(*,*) n(i),timeCol
        end do

        do i = 1,final
            resultRow = prodRow(M,v,n(final),timeRow)
            write(*,*) n(i),timeRow
        end do
    end program MatrizVetor