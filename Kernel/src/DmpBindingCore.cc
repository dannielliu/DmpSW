/*
 *  $Id: DmpBindingCore.cc, 2014-04-11 21:54:40 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpRunMode.h"
#include "DmpVSvc.h"    // included DmpDetectorID.h
#include "DmpVDataMgr.h"
#include "DmpVAlg.h"
#include "DmpAlgorithmManager.h"
#include "DmpServiceManager.h"

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
    // Wrap DmpVDataMgr
struct DmpVDataMgrWrapper : public DmpVDataMgr, boost::python::wrapper<DmpVDataMgr>{
  DmpVDataMgrWrapper():DmpVDataMgr(){}
  void BookBranch(){
    this->get_override("BookBranch")();
  }
  /*
  void ResetEvent(){
    this->get_override("ResetEvent")();
  }
  */
};

//-------------------------------------------------------------------
BOOST_PYTHON_MODULE(libDmpCore){
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
    .def("SetSubDet",   &DmpVSvc::SetSubDet)
  ;
  // DmpVDataMgr
  class_<DmpVDataMgrWrapper,boost::noncopyable>("DmpVDataMgr",init<>())
    .def("BookBranch",  pure_virtual(&DmpVDataMgr::BookBranch))
    //.def("ResetEvent",  pure_virtual(&DmpVDataMgr::ResetEvent))
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
    .def("GetInstance", &DmpAlgorithmManager::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
    .def("Append",  &DmpAlgorithmManager::Append)
    .def("Replace", &DmpAlgorithmManager::Replace)
    .def("Get",     &DmpAlgorithmManager::Get,return_value_policy<reference_existing_object>())
    .def("ListAllElements",&DmpAlgorithmManager::ListAllElements)
    .def("Initialize",  &DmpAlgorithmManager::Initialize)
    .def("Finalize",    &DmpAlgorithmManager::Finalize)
    .def("Process",     &DmpAlgorithmManager::Process)
  ;
  // DmpServiceManager
  class_<DmpServiceManager,boost::noncopyable>("DmpServiceManager",no_init)
    .def("GetInstance", &DmpServiceManager::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
    .def("Append",  &DmpServiceManager::Append)
    .def("Replace", &DmpServiceManager::Replace)
    .def("Get",     &DmpServiceManager::Get,return_value_policy<reference_existing_object>())
    .def("ListAllElements",&DmpServiceManager::ListAllElements)
    .def("Initialize",  &DmpServiceManager::Initialize)
    .def("Finalize",    &DmpServiceManager::Finalize)
  ;
}


