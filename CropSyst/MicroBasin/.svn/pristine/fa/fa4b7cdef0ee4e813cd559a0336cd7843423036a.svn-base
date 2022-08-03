#ifndef BALANCEITEM_H
#define BALANCEITEM_H
#include <string>

#define MASS_BALANCE_WATER_MM 0.000001
#define MASS_BALANCE_CHEMICAL_GRAM 0.000001

class BalanceItem
{
    double flux_in;         //Positive for flow in
    double flux_out;        //Positive for flow out
    double pool_init;
    double pool_final;
public:
    void SetFluxIn(double flxin) {flux_in = flxin;};
    void SetFluxOut(double flxout) {flux_out = flxout;};
    void SetInitPool(double initpool) {pool_init = initpool;};
    void SetFinalPool(double finalpool) {pool_final = finalpool;};
    double GetFluxIn() {return flux_in;};
    double GetFluxOut() {return flux_out;};
    double GetFinalPool() {return pool_final;};
    double GetInitPool() {return pool_init;};
    double AddFluxIn(double newflxin) {flux_in += newflxin;return flux_in;};
    double AddFluxOut(double newfluxout) {flux_out += newfluxout; return flux_out;};
    double SubFluxIn(double subflux) {flux_in -= subflux;return flux_in;};
    double SubFluxOut(double subflux) {flux_out -= subflux; return flux_out;};
    double AddInitPool(double addpool) {pool_init += addpool;return pool_init;};
    double AddFinalPool(double addpool) {pool_final += addpool;return pool_final;};
    double SubInitPool(double subpool) {pool_init -= subpool;return pool_init;};
    double SubFinalPool(double subpool) {pool_final -= subpool;return pool_final;};
    void ClearPoolAndFluxes();
    bool IsMassBalance(const double tol = 1e-8);
    void PrintMassBalanceTerms(std::string processname);
    BalanceItem();
};

#endif // BALANCEITEM_H
