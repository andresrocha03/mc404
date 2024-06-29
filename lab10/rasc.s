
recursive_tree_search:
    //root node em a0
    //val em a1

    mv t2, a0
    li a0, 0
    mv s0, sp
    sw ra, 0(sp)
    la ra, found_result

    search_value:
        addi sp, sp, -4
        sw ra, 0(sp)
        lw t1, 0(t2)
        addi a0, a0, 1
        beq t1, a1, found_result
    
    esquerda:
        //go left
        addi sp, sp, -4
        sw t2, 0(sp)
        lw t2, 4(t2) //left
        beq t2, zero, direita    
        jal search_value

    direita:
        lw t2, 0(sp)
        lw t2, 8(t2) //filho direito do pai
        beq t2, zero, nulo
        jal search_value

    nulo:
        addi sp, sp, 4
        lw ra, 0(sp)
        lw t2, 4(sp)
        addi a0, a0, -1
        ret
            
    found_result:
        mv sp, s0
        lw ra, 0(sp)
    ret