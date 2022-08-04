#ifndef UTIL_FACTORY_H
#define UTIL_FACTORY_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/mpi/MpiFileIo.h>         // member
#include <util/param/ParamComposite.h>  // used in implementation
#include <util/param/Begin.h>           // used in implementation
#include <util/param/Label.h>           // used in implementation
#include <util/param/End.h>             // used in implementation
#include <util/global.h>

#ifdef UTIL_MPI
#include <util/mpi/MpiSendRecv.h>
#endif

#include <string>

namespace Util
{

   /**
   * Factory template.
   *
   * \ingroup Manager_Module
   */
   template <typename Data>
   class Factory
   {

   public:

      /**
      * Constructor.
      */
      Factory();

      /**
      * Destructor.
      */
      virtual ~Factory();

      /**
      * Add a new subfactory to the list.
      *
      * \param subfactory New subfactory to be added
      */
      void addSubfactory(Factory<Data>& subfactory);

      /**
      * Returns a pointer to a new instance of specified subclass.
      *
      * This method takes the name className of a subclass of Data as a
      * parameter, and attempts to instantiate an object of that class.
      * If it recognizes the className, it creates an instance of that
      * class and returns a Data* base class pointer to the new object.
      * If it does not recognize the className, it returns a null pointer.
      *
      * An implementation should first call "trySubfactories(className)"
      * and immediately return if this returns a non-null pointer, before
      * attempting to match the className against specific strings.
      *
      * \param  className name of subclass
      * \return base class pointer to new object, or a null pointer.
      */
      virtual Data* factory(const std::string &className) const = 0;

      /**
      * Read a class name, instantiate an object, and read its parameters.
      *
      * This method:
      *  - reads a comment line of the form className + {
      *  - invokes the factory method to create an instance of className
      *    if className is recognized
      *  - invokes the readParam() method of the new object
      *  - throws an Exception if className is not recognized if isRequired
      *    is true.
      *  - returns a null pointer if className is not recognized if 
      *    isRequired is false.
      *
      * When compiled with MPI, if the parent ParamComposite has a param
      * communicator, this method reads the comment line on the Io processor,
      * broadcasts it to all others, and then lets each processor 
      * independently match this string. 
      *
      * \throws Exception if className is not recognized but is required.
      *
      * \param  in         input stream
      * \param  parent     parent ParamComposite object
      * \param  className  (output) name of subclass of Data
      * \param  isEnd      (output) is the input a closing bracket "}" ?
      * \param  isRequired is this object required? Default is true.
      * \return pointer to new instance of className
      */
      Data* readObject(std::istream &in, ParamComposite& parent,
                       std::string& className, bool& isEnd,
                       bool isRequired = true);

      /**
      * Read an optional class name, instantiate an object, and read its 
      * parameters.
      *
      * This method:
      *  - reads a comment line of the form className + {
      *  - invokes the factory method to create an instance of className
      *  - invokes the readParam() method of the new object if className
      *    is recognized.
      *  - returns a null pointer if className is not recognized.
      *
      * When compiled with MPI, if the parent ParamComposite has a param
      * communicator, this method reads the comment line on the Io processor,
      * broadcasts it to all others, and then lets each processor 
      * independently match this string. 
      *
      * \param  in         input stream
      * \param  parent     parent ParamComposite object
      * \param  className  (output) name of subclass of Data
      * \param  isEnd      (output) is the input a closing bracket "}" ?
      * \return pointer to new instance of className
      */
      Data* readObjectOptional(std::istream &in, ParamComposite& parent,
                       std::string& className, bool& isEnd);

      /**
      * Load a class name, instantiate an object, and load the object.
      *
      * This method:
      *  - loads a className from an input archive
      *  - invokes the factory method to create an instance of className
      *  - invokes the load() method of the new object
      *
      * When compiled with MPI, if the parent ParamComposite has a param
      * communicator, this method loads the comment line on the Io processor,
      * broadcasts it to all others, and then lets each processor 
      * independently match this string. 
      *
      * \throws Exception if className is not recognized.
      *
      * \param  ar        input/loading archive
      * \param  parent    parent ParamComposite object
      * \param  className (output) name of subclass of Data
      * \return pointer to new instance of className
      */
      Data* loadObject(Serializable::IArchive& ar, ParamComposite& parent,
                       std::string& className);

   protected:

      /**
      * Search through subfactories for match.
      *
      * This method iterates through all registered subfactories, calls
      * the factory(const std::string& ) method of each, and immediately
      * returns a pointer to a new object if any of them returns a non-null
      * pointer. If all of them return a null pointer, this method also
      * returns a null pointer.
      *
      * \param  className name of subclass
      * \return base class pointer to new object, or a null pointer.
      */
      Data* trySubfactories(const std::string& className) const;

      #ifdef UTIL_MPI
      /**
      * Set associated Mpi communicator.
      *
      * Is not recursive (is not applied to subfactories).
      *
      * \param communicator MPI Intra-communicator to use for input
      */
      void setIoCommunicator(MPI::Intracomm& communicator);

      /**
      * Does this factory have a param communicator?
      */
      bool hasIoCommunicator() const;
      #endif

   private:

      /// Vector of pointers to child factories.
      std::vector< Factory<Data>* > subfactories_;

      /// Object to identify if this processor can do file Io.
      MpiFileIo   paramFileIo_;

   };

   /*
   * Constructor.
   */
   template <typename Data>
   Factory<Data>::Factory()
    : paramFileIo_()
   {}

   /*
   * Destructor.
   */
   template <typename Data>
   Factory<Data>::~Factory()
   {}

   #ifdef UTIL_MPI
   /*
   * Set the param communicator.
   */
   template <typename Data>
   void Factory<Data>::setIoCommunicator(MPI::Intracomm& communicator)
   {
      if (paramFileIo_.hasIoCommunicator()) {
         if (&paramFileIo_.ioCommunicator() != &communicator) {
            UTIL_THROW("Attempt to modify Factory param communicator");
         }
      } else {
         paramFileIo_.setIoCommunicator(communicator);
      }
   }

   /*
   * Does thus factory have a param communicator?
   */
   template <typename Data>
   bool Factory<Data>::hasIoCommunicator() const
   {  return paramFileIo_.hasIoCommunicator(); }
   #endif

   /*
   * Add a subfactory to the list of children.
   */
   template <typename Data>
   void Factory<Data>::addSubfactory(Factory<Data>& subfactory)
   {  subfactories_.push_back(&subfactory); }




   /*
   * Read subclass name, create object, and read its parameters.
   */
   template <typename Data>
   Data* Factory<Data>::readObject(std::istream &in, ParamComposite& parent,
                                   std::string& className, bool& isEnd,
                                   bool isRequired)
   {
      Data*        typePtr = 0;
      int          length;
      bool         hasData = false; // initialized to avoid compiler warning

      #ifdef UTIL_MPI
      // Set ioCommunicator to that of parent, if any.
      if (parent.hasIoCommunicator()) {
         setIoCommunicator(parent.ioCommunicator());
      }
      #endif

      // Read a first line of the form "ClassName{" into Label::buffer
      if (paramFileIo_.isIoProcessor()) { 
         Label::read(in);

         if (Label::isClear()) { // Label did not successfully read a string
            if (isRequired) {
               Log::file() << "Empty required label read into Factory" 
                           << std::endl;
               UTIL_THROW("Empty required label read into Factory");
            } else { // return null pointer
               return 0;
            }
         }
      }

      #ifdef UTIL_MPI
      // Broadcast the full string to all processors.
      if (paramFileIo_.hasIoCommunicator()) {
         bcast<std::string>(paramFileIo_.ioCommunicator(), Label::buffer(), 0);
      }
      // Hereafter, each processor independently processes the same string.
      #endif
      length = Label::buffer().size();

      // If Label::buffer() = '}', set isEnd=true and return null ptr.
      if (length == 1 && Label::buffer()[0] == '}') {
         className = std::string();
         isEnd = true;
         Label::clear();
         Label::setIsMatched(true);
         return 0; 
      } else {
         isEnd = false;
      }

      // Isolate className by stripping the trailing "{" bracket
      if (Label::buffer()[length-1] == '{') {
         className = Label::buffer().substr(0, length-1);
         hasData = true;
      } else
      if (Label::buffer()[length-1]=='}' && Label::buffer()[length-2]=='{'){
         className = Label::buffer().substr(0, length-2);
         hasData = false;
      } else {
         if (paramFileIo_.isIoProcessor()) {
            className = std::string();
            Log::file() << "Invalid string: " << Label::buffer() << std::endl;
            UTIL_THROW("Invalid first line\n");
         }
      }

      // Create new object of the specified class.
      typePtr = factory(className);

      // If the subclass name was recognized:
      if (typePtr) {

         // Clear the Label object and set Label::isMatched to true
         Label::clear();
         Label::setIsMatched(true);

         // Add Begin object to new child ParamComposite, indented for child.
         Begin* beginPtr;
         beginPtr = &typePtr->addBegin(className.c_str());
         beginPtr->setIndent(parent);

         // Echo Begin object, if appropriate
         if (ParamComponent::echo() && paramFileIo_.isIoProcessor()) {
            beginPtr->writeParam(Log::file());
         }

         // Add child to parent
         parent.addParamComposite(*typePtr);

         // Read parameters for the new child object, if any
         if (hasData) {
            typePtr->readParameters(in);
         }

         // Process end bracket
         if (hasData) {
            // Read closing bracket, set indentation as for child.
            typePtr->readEnd(in).setIndent(parent);
         } else {
            // Add End object without reading
            End* endPtr;
            endPtr = &typePtr->addEnd();
            endPtr->setIndent(parent);
         }

         // Note: The readParameters() methods for managed objects should 
         // not read begin and end lines, which are read here. 

      } else {

         Label::setIsMatched(false);

         if (isRequired) {
            std::string msg = "Factory was unable to match line: " 
                              + Label::buffer();
            UTIL_THROW(msg.c_str());
         }

      }
      return typePtr;
   }

   /*
   * Read optional subclass name, create object, and read its parameters.
   */
   template <typename Data>
   Data* 
   Factory<Data>::readObjectOptional(std::istream &in, 
                                     ParamComposite& parent,
                                     std::string& className, bool& isEnd)
   {  return readObject(in, parent, className, isEnd, false); }

   /*
   * Load subclass name, create object, and load object.
   */
   template <typename Data>
   Data* Factory<Data>::loadObject(Serializable::IArchive& ar, 
                                   ParamComposite& parent,
                                   std::string& className)
   {
      #ifdef UTIL_MPI
      // Set ioCommunicator to that of parent, if any.
      if (parent.hasIoCommunicator()) {
         setIoCommunicator(parent.ioCommunicator());
      }
      #endif

      // Read the class name.
      if (paramFileIo_.isIoProcessor()) {
         ar & className;
      }

      #ifdef UTIL_MPI
      // Broadcast the full string to all processors.
      if (paramFileIo_.hasIoCommunicator()) {
         bcast<std::string>(paramFileIo_.ioCommunicator(), className, 0);
      }
      #endif

      // Create and load a new object of the specified class.
      Data* typePtr = factory(className);
      if (typePtr) {
         parent.loadParamComposite(ar, *typePtr);
      } else {
         Log::file() << "Failed attempt to create instance of " 
                     << className << std::endl;
      }
      return typePtr;
   }

   /*
   * Try all subfactories in sequence searching for a match.
   */
   template <typename Data>
   Data* Factory<Data>::trySubfactories(const std::string& className) 
   const
   {
      Data* typePtr = 0;
      int n = subfactories_.size();
      for (int i = 0; i < n && typePtr == 0; ++i) {
         typePtr = subfactories_[i]->factory(className);
      }
      return typePtr;
   }

}
#endif
