//all values are multiplied by 100,000 to make them larger ints to work with
//id, iq, and omega are the most recent actual measured values

int qDecoupling(int qPIOutput, int id, int Ls, int omega, int Ke, int OutputMax){
    int hold = qPIOutput + id*Ls*omega + Ke*omega;
    if(hold < OutputMax && hold > -OutputMax)
        return hold;
    else if(hold >= OutputMax)
        return OutputMax;
    else
        return -OutputMax;
}

int dDecoupling(int dPIOutput, int iq, int Ls, int omega, int OutputMax){
    int hold = dPIOutput - omega*Ls*iq;
    if(hold < OutputMax && hold > -OutputMax)
        return hold;
    else if(hold >= OutputMax)
        return OutputMax;
    else
        return -OutputMax;
}
