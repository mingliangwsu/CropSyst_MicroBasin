# at this point the CWD should be dev
rootdir="$PWD"                                                                                                                 
echo make common simulation                                                                                                                            
cd ${rootdir}/common/simulation/build/gcc/Release                                                                                                             
rm *.o  *.a                                                                                                                                            
make                                                                                                                                                   
echo make common                                                                                                                                       
cd ${rootdir}/common/weather/build/gcc/Release                                                                                                                
rm *.o  *.a                                                                                                                                            
make                                                                                                                                                   
echo make corn                                                                                                                                         
cd ${rootdir}/corn/build/gcc/Release                                                                                                                          
rm *.o  *.a                                                                                                                                            
make                                                                                                                                                   
echo make UED library                                                                                                                                  
cd ${rootdir}/UED/library/build/gcc/Release                                                                                                                   
rm *.o  *.a                                                                                                                                            
make                                                                                                                                                   
echo make CS_suite                                                                                                                                     
cd ${rootdir}/CS_suite/build/gcc/Release                                                                                                                      
rm *.o  *.a                                                                                                                                            
make                                                                                                                                                   
echo make CropSyst                                                                                                                                    
cd ${rootdir}/CropSyst/MicroBasin/build/library/gcc/Release                                                                                                              
rm *.o  *.a
make                                                                                                                                                 
echo make MicroBasin                                                                                                                                    
cd ${rootdir}/CropSyst/MicroBasin/build/gcc/Release                                                                                                           
rm *.o  *.a
make 

cd ${rootdir}      
