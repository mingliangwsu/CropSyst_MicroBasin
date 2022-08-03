

#define WANT_STREAM
#define WANT_MATH

#include "include.h"
#include "str.h"
#include "format.h"


#ifdef use_namespace
using namespace RBD_STRING;              // access RBD_STRING namespace
#endif



int main()
{
   int i, j;

   Format F1;
   F1.OverFlowPolicy(Format::E);
   F1.UnderFlowPolicy(Format::E);
   F1.FormatType(Format::DEC_FIGS);
   F1.Precision(2);
   F1.MinWidth(10);
   F1.MaxWidth(10);
   F1.Alignment(Format::RIGHT);
   F1.Positive(Format::NX);

   Format F2;
   F2.OverFlowPolicy(Format::E);
   F2.UnderFlowPolicy(Format::E);
   F2.FormatType(Format::DEC_FIGS);
   F2.Precision(2);
   F2.MinWidth(10);
   F2.MaxWidth(20);
   F2.Alignment(Format::RIGHT);
   F2.Positive(Format::NX);

   Format F3;
   F3.OverFlowPolicy(Format::E);
   F3.UnderFlowPolicy(Format::E);
   F3.FormatType(Format::SCIENTIFIC);
   F3.Precision(2);
   F3.MinWidth(15);
   F3.MaxWidth(15);
   F3.Alignment(Format::RIGHT);
   F3.Positive(Format::NX);

   Format F4;
   F4.OverFlowPolicy(Format::E);
   F4.UnderFlowPolicy(Format::E);
   F4.FormatType(Format::SCIENTIFIC);
   F4.Precision(3);
   F4.MinWidth(15);
   F4.MaxWidth(30);
   F4.Alignment(Format::RIGHT);
   F4.Positive(Format::NX);

   Format F5;
   F5.OverFlowPolicy(Format::E);
   F5.UnderFlowPolicy(Format::ZERO);
   F5.FormatType(Format::SIG_FIGS);
   F5.Precision(2);
   F5.MinWidth(10);
   F5.MaxWidth(10);
   F5.Alignment(Format::RIGHT);
   F5.Positive(Format::NX);

   Format F6;
   F6.OverFlowPolicy(Format::E);
   F6.UnderFlowPolicy(Format::ZERO);
   F6.FormatType(Format::SIG_FIGS);
   F6.Precision(3);
   F6.MinWidth(10);
   F6.MaxWidth(30);
   F6.Alignment(Format::RIGHT);
   F6.Positive(Format::NX);

   Format F7;
   F7.OverFlowPolicy(Format::E);
   F7.UnderFlowPolicy(Format::ZERO);
   F7.FormatType(Format::SIG_FIGS);
   F7.Precision(3);
   F7.MinWidth(10);
   F7.MaxWidth(10);
   F7.Alignment(Format::RIGHT);
   F7.Positive(Format::NX);
   F7.Variant(Format::VAR1);

   Format F8;
   F8.OverFlowPolicy(Format::E);
   F8.UnderFlowPolicy(Format::ZERO);
   F8.FormatType(Format::SIG_FIGS);
   F8.Precision(6);
   F8.MinWidth(8);
   F8.MaxWidth(8);
   F8.Alignment(Format::RIGHT);
   F8.Positive(Format::SPACE);
   F8.Variant(Format::VAR1);

   Format F9;
   F9.OverFlowPolicy(Format::E);
   F9.UnderFlowPolicy(Format::E);
   F9.FormatType(Format::SIG_FIGS);
   F9.Precision(6);
   F9.MinWidth(8);
   F9.MaxWidth(8);
   F9.Alignment(Format::RIGHT);
   F9.Positive(Format::SPACE);
   F9.Variant(Format::VAR1);
   
   Format F10;
   F10.OverFlowPolicy(Format::E);
   F10.UnderFlowPolicy(Format::E);
   F10.FormatType(Format::SIG_FIGS);
   F10.Precision(6);
   F10.MinWidth(8);
   F10.MaxWidth(8);
   F10.Alignment(Format::RIGHT);
   F10.Positive(Format::NX);
   F10.Variant(Format::VAR1);
   
   cout << "spot checks" << endl << endl;

   cout << F2 << "short" << '*' << endl;
   cout << F2 << "1234567890" << '*' << endl;
   cout << F2 << "1234567890A" << '*' << endl;
   cout << F2 << "1234567890ABCDEFGHIJ" << '*' << endl;
   cout << F2 << "1234567890ABCDEFGHIJK" << '*' << endl;
   cout << endl;



   double A[] = { 0.0, 0.50, 0.949, 0.951, 0.992, 0.996, 1.000, 1.001, 2.93,
      2.96, 2.993, 2.996, 3.000, 3.001, 3.6 };
   double B[] = { 1.0e-150, 1.0e-101, 1.0e-100, 1.0e-99, 1.0e-10, 0.001, 0.1,
      1.00, 10, 1000, 10000, 100000, 1000000, 10000000, 1.0e+99, 1.0e+100,
      1.0e+101, 1.0e+150 };

   cout << "spot check rounding" << endl << endl;
   
   Format F5X = F5; F5X.Precision(1);

   cout << F6 << A[0] << A[2] << A[3] << A[4] << A[5] << A[6] << endl;
   cout << F5 << A[0] << A[2] << A[3] << A[4] << A[5] << A[6] << endl;
   cout << F5X << A[0] << A[2] << A[3] << A[4] << A[5] << A[6] << endl << endl;

   cout << "test formats over a wide range of sizes" << endl << endl;

   for (j = 0; j < 18; j++)
      for (i = 0; i <  15; i++)
         if ( ((i == 0) && (j == 0)) || i != 0)
         {
            double x = A[i] * B[j];
            cout << "12345678901234567890" << endl;
            cout << F1 << x << '*' << endl;
            cout << F2 << x << '*' << endl;
            cout << F3 << x << '*' << endl;
            cout << F4 << x << '*' << endl;
            cout << F5 << x << '*' << endl;
            cout << F6 << x << '*' << endl;
            cout << F7 << x << '*' << endl;
            cout << F8 << x << '*' << endl;
            cout << F9 << x << '*' << endl;
            cout << F10 << x << '*' << endl;
            cout << endl;
         }

   cout << "testing OstreamWithFormat as destination" << endl << endl;
   cout << F1 << 2.34563 << 5.432160 << F3 << 7.45638 << endl;
   OstreamWithFormat f1(cout, F1);
   OstreamWithFormat f3(cout, F3);
   f1 << 2.34563 << 5.432160; f3 << 7.45638 << endl;
   cout << endl;
   
   cout << "testing rounding with scientific format around E-100" << endl
       << endl;

   double C[] = { .49, .51, .949, .951, .9949, .9951, .99949, .99951,
      .999949, .999951, .9999949, .9999951 };
   Format SCIX;
   SCIX.FormatType(Format::SCIENTIFIC);
   SCIX.Precision(7);
   SCIX.Width(13);
   SCIX.Suffix("|");
   
   for (i = 0; i < 12; ++i)
   {
      for (j = 13; j >= 4; --j)
      {
         SCIX.Width(j); SCIX.Prefix(String(13-j,' '));
         cout << SCIX << C[i] * 1E-98 << C[i] * 1E-99 << C[i] * 1E-100; 
         cout << SCIX << -C[i] * 1E-98 << -C[i] * 1E-99 << -C[i] * 1E-100;
         cout << endl;
      }
      cout << endl;
   } 
   
   cout << endl;
   
   cout << "demonstrate a variety of formats" << endl << endl;

   // Scientific format
   Format SCI;
   SCI.FormatType(Format::SCIENTIFIC);
   SCI.Precision(8);
   SCI.Width(14);
   SCI.Suffix("|");

   // Decimal format - switch to scientific on under-flow or over-flow
   Format DEC1;
   DEC1.UnderFlowPolicy(Format::E);
   DEC1.FormatType(Format::DEC_FIGS);
   DEC1.Precision(4);
   DEC1.Width(12);
   DEC1.Suffix("|");

   // Decimal format - no action on under-flow; hashes on over-flow
   Format DEC2;
   DEC2.OverFlowPolicy(Format::HASH);
   DEC2.FormatType(Format::DEC_FIGS);
   DEC2.Precision(4);
   DEC2.Width(12);
   DEC2.Suffix("|");

   // Significant figures - switch to scientific on under-flow or over-flow 
   Format SIG1;
   SIG1.UnderFlowPolicy(Format::E);
   SIG1.FormatType(Format::SIG_FIGS);
   SIG1.Precision(8);
   SIG1.Width(11);
   SIG1.Positive(Format::SPACE);
   SIG1.Prefix(" ");
   SIG1.Suffix("|");

   // Significant figures - reduce precision on under-flow; hashes on over-flow
   Format SIG2;
   SIG2.OverFlowPolicy(Format::HASH);
   SIG2.FormatType(Format::SIG_FIGS);
   SIG2.Precision(8);
   SIG2.Width(11);
   SIG2.Positive(Format::SPACE);
   SIG2.Prefix(" ");
   SIG2.Suffix("|");

   // Significant figures - reduce precision on under-flow;
   // scientific on over-flow; pretty variant
   Format SIG3;
   SIG3.UnderFlowPolicy(Format::ZERO);
   SIG3.OverFlowPolicy(Format::E);
   SIG3.FormatType(Format::SIG_FIGS);
   SIG3.Precision(8);
   SIG3.Width(10);
   SIG3.Positive(Format::SPACE);
   SIG3.Prefix(" ");
   SIG3.Suffix("|");
   SIG3.Variant(Format::VAR1);

   // Integer format - switch to scientific on over-flow
   Format INT;
   INT.FormatType(Format::INTEGER);
   INT.Width(12);

   double x = 1.23456789;
   double mult[] = {0, 1E-100, 1E-20, 0.0001, 0.1, 1, 10, 1000, 1E7, 1E8, 1E9,
      1E10, 1E20, 1E100};
   cout << SCI << "SCIENTFIC" << DEC1 << "DEC 1" << DEC2 << "DEC 2"
      << SIG1 << "SIG 1" << SIG2 << "SIG 2" << SIG3 << "SIG 3"
      << INT << "INTEGER" << endl;

   for (i = 0; i < 14; ++i)
   {
      double y = x * mult[i];
      cout << SCI << y << DEC1 << y << DEC2 << y << SIG1 << y
         << SIG2 << y << SIG3 << y << INT << y << endl;
   }
   cout << endl;

   // do the same for negative

   for (i = 0; i < 14; ++i)
   {
      double y = - x * mult[i];
      cout << SCI << y << DEC1 << y << DEC2 << y << SIG1 << y
         << SIG2 << y << SIG3 << y << INT << y << endl;
   }
   cout << endl;


   return 0;
}


