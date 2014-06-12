/*
 *  $Id: DmpBindingKernel.cc, 2014-05-04 15:31:47 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpRunMode.h"
#include "DmpDetectorID.h"
#include "DmpVSvc.h"
#include "DmpVAlg.h"
#include "DmpAlgorithmManager.h"
#include "DmpServiceManager.h"
#include "DmpCore.h"

//-------------------------------------------------------------------
    // Wrap DmpVAlg
struct DmpVAlgWrapper : public DmpVAlg, boost::python::wrapper<DmpVAlg>{
  DmpVAlgWrapper(const std::string &n):DmpVAlg(n){}
  bool Initialize(){
    return this->get_override("Initialize")();
  }
  bool ProcessThisEvent(){
    return this->get_override("ProcessThisEvent")();
  }
  bool Finalize(){
    return this->get_override("Finalize")();
  }
  void Set(const std::string &type,const std::string &argv){
    if(boost::python::override Set = this->get_override("Set")(type,argv)){
      Set(type,argv);
    }else{
      DmpVAlg::Set(type,argv);
    }
  }
  void Default_Set(const std::string &type,const std::string &argv){
    this->DmpVAlg::Set(type,argv);
  }
};
    // Wrap DmpVSvc
struct DmpVSvcWrapper : public DmpVSvc, boost::python::wrapper<DmpVSvc>{
  DmpVSvcWrapper(const std::string &n):DmpVSvc(n){}
  bool Initialize(){
    return this->get_override("Initialize")();
  }
  bool Finalize(){
    return this->get_override("Finalize")();
  }
  void Set(const std::string &type,const std::string &argv){
    if(boost::python::override Set = this->get_override("Set")(type,argv)){
      Set(type,argv);
    }else{
      DmpVSvc::Set(type,argv);
    }
  }
  void Default_Set(const std::string &type,const std::string &argv){
    this->DmpVSvc::Set(type,argv);
  }
};

//-------------------------------------------------------------------
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(SetLogLevel_Wrap,DmpCore::SetLogLevel,1,2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(SetRandomSeed_Wrap,DmpCore::SetRandomSeed,0,1)

//-------------------------------------------------------------------
BOOST_PYTHON_MODULE(libDmpKernel){
  using namespace boost::python;
  // DmpRunMode
  enum_<DmpDetector::DmpERunMode>("DmpERunMode")
    .value("kUnknow",   DmpDetector::kUnknow)
    .value("k0Compress",DmpDetector::k0Compress)
    .value("kCompress", DmpDetector::kCompress)
    .value("kCalPed",   DmpDetector::kCalPed)
    .value("kCalADC",   DmpDetector::kCalADC)
  ;
  // DmpDetectorID
  enum_<DmpDetector::DmpEDetectorID>("DmpEDetectorID")
    .value("kPsd",  DmpDetector::kPsd)
    .value("kStk",  DmpDetector::kStk)
    .value("kBgo",  DmpDetector::kBgo)
    .value("kNud",  DmpDetector::kNud)
    .value("kWhole",DmpDetector::kWhole)
  ;
  // DmpVSvc
  class_<DmpVSvcWrapper,boost::noncopyable>("DmpVSvc",init<std::string>())
    .def("Initialize",  pure_virtual(&DmpVSvc::Initialize))
    .def("Finalize",    pure_virtual(&DmpVSvc::Finalize))
    .def("Set", &DmpVSvc::Set,  &DmpVSvcWrapper::Default_Set)
  ;
  // DmpVAlg
  class_<DmpVAlgWrapper,boost::noncopyable>("DmpVAlg",init<std::string>())
    .def("Initialize",      pure_virtual(&DmpVAlg::Initialize))
    .def("ProcessThisEvent",pure_virtual(&DmpVAlg::ProcessThisEvent))
    .def("Finalize",        pure_virtual(&DmpVAlg::Finalize))
    .def("Set", &DmpVAlg::Set,  &DmpVAlgWrapper::Default_Set)
  ;
  // DmpAlgorithmManager
  class_<DmpAlgorithmManager,boost::noncopyable>("DmpAlgorithmManager",no_init)
// *
// *  TODO:  only keep Append
// *
    .def("Append",  &DmpAlgorithmManager::Append)
    //.def("Replace", &DmpAlgorithmManager::Replace)
    //.def("Get",     &DmpAlgorithmManager::Get,return_value_policy<reference_existing_object>())
    .def("ListAllElements",&DmpAlgorithmManager::ListAllElements)
  ;
  // DmpServiceManager
  class_<DmpServiceManager,boost::noncopyable>("DmpServiceManager",no_init)
// *
// *  TODO:     only keep Append
// *
    .def("Append",  &DmpServiceManager::Append)
    //.def("Replace", &DmpServiceManager::Replace)
    .def("Get",     &DmpServiceManager::Get,return_value_policy<reference_existing_object>())
    .def("ListAllElements",&DmpServiceManager::ListAllElements)
  ;
  // DmpCore
  class_<DmpCore,boost::noncopyable>("DmpCore",no_init)
    .def("GetInstance", &DmpCore::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
    .def("Initialize",  &DmpCore::Initialize)
    .def("Run",         &DmpCore::Run)
    .def("Finalize",    &DmpCore::Finalize)
    .def("SetLogLevel", &DmpCore::SetLogLevel, SetLogLevel_Wrap())
    .def("SetRandomSeed",&DmpCore::SetRandomSeed, SetRandomSeed_Wrap())
    .def("SetMaxEventNumber", &DmpCore::SetMaxEventNumber)
    .def("SetTimeWindow", &DmpCore::SetTimeWindow)
    .def("AlgorithmManager",    &DmpCore::AlgorithmManager,return_value_policy<reference_existing_object>())
    .def("ServiceManager",      &DmpCore::ServiceManager,return_value_policy<reference_existing_object>())
  ;

}


