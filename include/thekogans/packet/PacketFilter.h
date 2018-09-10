// Copyright 2016 Boris Kogan (boris@thekogans.net)
//
// This file is part of libthekogans_packet.
//
// libthekogans_packet is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libthekogans_packet is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libthekogans_packet. If not, see <http://www.gnu.org/licenses/>.

#if !defined (__thekogans_packet_PacketFilter_h)
#define __thekogans_packet_PacketFilter_h

#include "thekogans/util/Types.h"
#include "thekogans/util/RefCounted.h"
#include "thekogans/packet/Config.h"
#include "thekogans/packet/Packet.h"

namespace thekogans {
    namespace packet {

        /// \brief
        /// Forward declaration of PacketFilter.
        struct PacketFilter;

        enum {
            /// \brief
            /// PacketFilterList list id.
            PACKET_FILTER_LIST_ID
        };

        /// \brief
        /// Convenient typedef for util::IntrusiveList<PacketFilter, PACKET_FILTER_LIST_ID>.
        typedef util::IntrusiveList<PacketFilter, PACKET_FILTER_LIST_ID> PacketFilterList;

        // Did I mention M$ is a brain dead company? Here's another
        // example of their stupidity and the hoops we have to jump
        // through to get around the obstacles they throw our way.
    #if defined (_MSC_VER)
        #pragma warning (push)
        #pragma warning (disable : 4275)
    #endif // defined (_MSC_VER)

        /// \struct PacketFilter PacketFilter.h thekogans/packet/PacketFilter.h
        ///
        /// \brief
        /// PacketFilter .

        struct _LIB_THEKOGANS_PACKET_DECL PacketFilter :
                public util::ThreadSafeRefCounted,
                public PacketFilterList::Node {
            /// \brief
            /// Convenient typedef for util::ThreadSafeRefCounted::Ptr<PacketFilter>.
            typedef util::ThreadSafeRefCounted::Ptr<PacketFilter> Ptr;

            /// \brief
            /// dtor.
            virtual ~PacketFilter () {}

            virtual Packet::Ptr FilterPacket (Packet::Ptr /*packet*/) = 0;

        protected:
            /// \brief
            /// If there's a next packet filter, pass the packet to it,
            /// otherwise just return it unchanged.
            /// \param[in] packet \see{Packet} to pass to the next filter.
            /// \return Either the results of next packet filter (if there is one),
            /// or an unchanged packet.
            inline Packet::Ptr CallNextPacketFilter (Packet::Ptr packet) const {
                return next != 0 ? next->FilterPacket (packet) : packet;
            }
        };

    #if defined (_MSC_VER)
        #pragma warning (pop)
    #endif // defined (_MSC_VER)

    } // namespace packet
} // namespace thekogans

#endif // !defined (__thekogans_packet_PacketFilter_h)