// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2017.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Hannes Roest $
// $Authors: Hannes Roest $
// --------------------------------------------------------------------------

#ifndef OPENMS_FORMAT_DATAACCESS_MSDATACACHEDCONSUMER_H
#define OPENMS_FORMAT_DATAACCESS_MSDATACACHEDCONSUMER_H

#include <OpenMS/INTERFACES/IMSDataConsumer.h>

#include <OpenMS/KERNEL/StandardTypes.h>

#include <OpenMS/FORMAT/CachedMzML.h>


namespace OpenMS
{
  class MSSpectrum;
  class MSChromatogram;

    /**
      @brief Transforming and cached writing consumer of MS data

      Is able to transform a spectrum on the fly while it is read using a
      function pointer that can be set on the object. The spectra is then
      cached to disk using the functions provided in CachedmzML.
    */
    class OPENMS_DLLAPI MSDataCachedConsumer :
      public CachedmzML,
      public Interfaces::IMSDataConsumer
    {
      typedef MSSpectrum SpectrumType;
      typedef MSChromatogram ChromatogramType;

    public:

      /**
        @brief Constructor

        Opens the output file and writes the header.
      */
      MSDataCachedConsumer(const String& filename, bool clearData=true);

      /**
        @brief Destructor

        Closes the output file and writes the footer.
      */
      ~MSDataCachedConsumer() override;

      /**
        @brief Write a spectrum to the output file
      */
      void consumeSpectrum(SpectrumType & s) override;

      /**
        @brief Write a chromatogram to the output file
      */
      void consumeChromatogram(ChromatogramType & c) override;

      void setExpectedSize(Size /* expectedSpectra */, Size /* expectedChromatograms */) override {;}

      void setExperimentalSettings(const ExperimentalSettings& /* exp */) override {;}

    protected:
      std::ofstream ofs_;
      bool clearData_;
      Size spectra_written_;
      Size chromatograms_written_;

    };

} //end namespace OpenMS

#endif
