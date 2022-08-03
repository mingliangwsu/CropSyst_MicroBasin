#ifndef distribution_normalH
#define distribution_normalH
namespace CORN {
//______________________________________________________________________________
class  Distribution_normal
{
public:
//NYN   Distribution_normal();
public: // Cumulative distribution functions
   double standard_CDF(double u)                                           const;
   double inverse_standard_CDF(double p)                                   const;
public: // Probability distribution functions
   double standard_PDF(double u)                                           const;
   double quad8_standard_PDF(double a, double b, double Q = 1.0)           const;
   // An implementation of adaptive, recursive Newton-Cotes integration.
private:
   double random_normal()                                                  const;
};
//______________________________________________________________________________
} // namespace CORN

#endif


