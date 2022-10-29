
gcc main.c ./layers/physical.c ./layers/data_link.c ./layers/application.c -o main

# clear files
echo | grep 'CLEAR' > ./bin/filename.binf
echo | grep 'CLEAR' > ./bin/filename.chck
echo | grep 'CLEAR' > ./bin/filename.done
echo | grep 'CLEAR' > ./bin/filename.outf
echo | grep 'CLEAR' > ./bin/filename.inpf

# execute test case 1
echo "-----------------------------------------------------------------------"
echo "Executing Alphabet Test:"
echo
echo "abcdefghijklmnopqrstuvwxyz" > bin/filename.inpf
echo "Input:"
echo "abcdefghijklmnopqrstuvwxyz"
echo 
echo "Result:"
./main
echo
echo "Expected:"
echo "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
echo "-----------------------------------------------------------------------"

# execute test case 2
echo "-----------------------------------------------------------------------"
echo "Executing Numerical Test:"
echo
echo "0123456789" > bin/filename.inpf
echo "Input:"
echo "0123456789"
echo 
echo "Result:"
./main
echo
echo "Expected:"
echo "0123456789"
echo "-----------------------------------------------------------------------"

# execute test case 3
echo "-----------------------------------------------------------------------"
echo "Executing Symbol Test:"
echo
echo "!@#$%^&*()-+={}[]:;<>?" > bin/filename.inpf
echo "Input:"
echo "!@#$%^&*()-+={}[]:;<>?"
echo
echo "Result:"
./main
echo
echo "Expected:"
echo "!@#$%^&*()-+={}[]:;<>?"
echo "-----------------------------------------------------------------------"

# execute test case 4
echo "-----------------------------------------------------------------------"
echo "Executing Large Dataset Test:"
echo
echo "Lorem ipsum dolor sit amet consectetur, adipisicing elit. Pariatur, aliquam. Ex earum aliquam omnis dicta nulla cumque id accusamus recusandae nam, fugit deleniti exercitationem quia labore suscipit molestiae quidem. Velit omnis a quisquam provident earum ab id sed vitae! Sit natus doloremque id, facilis eius eos rem sunt. Iste iure quidem voluptas illo facilis, veritatis blanditiis, facere perferendis incidunt odit fugit corporis? Atque tempora laudantium, id neque porro, libero labore provident perspiciatis quisquam qui corrupti velit perferendis dolores, ad natus facilis nisi! Iusto in, adipisci aliquam error dolor, perferendis dolorem rerum doloremque porro tempore nostrum soluta aut obcaecati modi iste eveniet itaque corporis quo, ratione sit ipsum! Alias harum asperiores, quae quia iure impedit inventore iusto quo ab eaque expedita quam voluptatibus. Et consequuntur nam animi itaque repellat laboriosam earum voluptatibus. Accusamus qui possimus ducimus consequuntur porro, rerum quaerat, corporis ipsum dolore quisquam exercitationem ipsa a pariatur natus fuga sequi. Consequuntur enim natus eum repellendus maxime. Iste fuga voluptatibus consequuntur, veritatis rem accusantium cumque earum quis ratione vero porro, minima natus, beatae est! Accusantium magni autem odit quis earum neque voluptas tenetur mollitia dolorem maiores eius dignissimos id delectus numquam, consequuntur odio impedit quos vero cumque quod asperiores necessitatibus nam distinctio sequi. Iusto molestiae maxime fugiat temporibus adipisci ex mollitia optio sequi voluptate! Eius adipisci temporibus nihil saepe id necessitatibus quia doloribus. Ex animi neque tenetur ipsam, reprehenderit aliquid vitae cum eveniet doloribus dolorem voluptatibus distinctio impedit nemo aliquam? Obcaecati impedit recusandae distinctio eos molestiae soluta vero culpa quis non, totam doloribus. Deserunt nulla officiis alias vitae. Blanditiis veritatis alias sint commodi minus, cum quos atque molestias aut eius nostrum dolores dolore distinctio neque illo ab aliquam at vel. Accusamus maiores quaerat rem, asperiores dolores praesentium aut, voluptate consequuntur tenetur sint, consectetur laboriosam! Officia dolore quidem adipisci illo minima fuga, repellendus ut architecto facilis maxime molestiae, pariatur repellat nam dolor earum cupiditate. Veniam rerum porro illo iste totam consequuntur iusto voluptate et culpa. Sequi at soluta numquam laudantium? Quo enim architecto aspernatur beatae, corrupti deleniti? Doloremque sunt pariatur omnis optio aut ducimus incidunt impedit, hic et consequatur placeat id ipsam illum nobis! Sit veritatis repudiandae reprehenderit consectetur dolorem esse nam laudantium aspernatur in tenetur incidunt nesciunt quaerat hic perferendis doloribus praesentium debitis deserunt, ipsam inventore animi accusantium et voluptatem! Placeat tempora nam nihil. Quaerat est numquam quae doloribus quis dolores maiores et excepturi nesciunt rem deleniti, quas repellat omnis quibusdam." > bin/filename.inpf
echo "Input:" 
echo "Lorem ipsum dolor sit amet consectetur, adipisicing elit. Pariatur, aliquam. Ex earum aliquam omnis dicta nulla cumque id accusamus recusandae nam, fugit deleniti exercitationem quia labore suscipit molestiae quidem. Velit omnis a quisquam provident earum ab id sed vitae! Sit natus doloremque id, facilis eius eos rem sunt. Iste iure quidem voluptas illo facilis, veritatis blanditiis, facere perferendis incidunt odit fugit corporis? Atque tempora laudantium, id neque porro, libero labore provident perspiciatis quisquam qui corrupti velit perferendis dolores, ad natus facilis nisi! Iusto in, adipisci aliquam error dolor, perferendis dolorem rerum doloremque porro tempore nostrum soluta aut obcaecati modi iste eveniet itaque corporis quo, ratione sit ipsum! Alias harum asperiores, quae quia iure impedit inventore iusto quo ab eaque expedita quam voluptatibus. Et consequuntur nam animi itaque repellat laboriosam earum voluptatibus. Accusamus qui possimus ducimus consequuntur porro, rerum quaerat, corporis ipsum dolore quisquam exercitationem ipsa a pariatur natus fuga sequi. Consequuntur enim natus eum repellendus maxime. Iste fuga voluptatibus consequuntur, veritatis rem accusantium cumque earum quis ratione vero porro, minima natus, beatae est! Accusantium magni autem odit quis earum neque voluptas tenetur mollitia dolorem maiores eius dignissimos id delectus numquam, consequuntur odio impedit quos vero cumque quod asperiores necessitatibus nam distinctio sequi. Iusto molestiae maxime fugiat temporibus adipisci ex mollitia optio sequi voluptate! Eius adipisci temporibus nihil saepe id necessitatibus quia doloribus. Ex animi neque tenetur ipsam, reprehenderit aliquid vitae cum eveniet doloribus dolorem voluptatibus distinctio impedit nemo aliquam? Obcaecati impedit recusandae distinctio eos molestiae soluta vero culpa quis non, totam doloribus. Deserunt nulla officiis alias vitae. Blanditiis veritatis alias sint commodi minus, cum quos atque molestias aut eius nostrum dolores dolore distinctio neque illo ab aliquam at vel. Accusamus maiores quaerat rem, asperiores dolores praesentium aut, voluptate consequuntur tenetur sint, consectetur laboriosam! Officia dolore quidem adipisci illo minima fuga, repellendus ut architecto facilis maxime molestiae, pariatur repellat nam dolor earum cupiditate. Veniam rerum porro illo iste totam consequuntur iusto voluptate et culpa. Sequi at soluta numquam laudantium? Quo enim architecto aspernatur beatae, corrupti deleniti? Doloremque sunt pariatur omnis optio aut ducimus incidunt impedit, hic et consequatur placeat id ipsam illum nobis! Sit veritatis repudiandae reprehenderit consectetur dolorem esse nam laudantium aspernatur in tenetur incidunt nesciunt quaerat hic perferendis doloribus praesentium debitis deserunt, ipsam inventore animi accusantium et voluptatem! Placeat tempora nam nihil. Quaerat est numquam quae doloribus quis dolores maiores et excepturi nesciunt rem deleniti, quas repellat omnis quibusdam." 
echo
echo "Result:"
./main
echo
echo "Expected:"
echo "LOREM IPSUM DOLOR SIT AMET CONSECTETUR, ADIPISICING ELIT. PARIATUR, ALIQUAM. EX EARUM ALIQUAM OMNIS DICTA NULLA CUMQUE ID ACCUSAMUS RECUSANDAE NAM, FUGIT DELENITI EXERCITATIONEM QUIA LABORE SUSCIPIT MOLESTIAE QUIDEM. VELIT OMNIS A QUISQUAM PROVIDENT EARUM AB ID SED VITAE! SIT NATUS DOLOREMQUE ID, FACILIS EIUS EOS REM SUNT. ISTE IURE QUIDEM VOLUPTAS ILLO FACILIS, VERITATIS BLANDITIIS, FACERE PERFERENDIS INCIDUNT ODIT FUGIT CORPORIS? ATQUE TEMPORA LAUDANTIUM, ID NEQUE PORRO, LIBERO LABORE PROVIDENT PERSPICIATIS QUISQUAM QUI CORRUPTI VELIT PERFERENDIS DOLORES, AD NATUS FACILIS NISI! IUSTO IN, ADIPISCI ALIQUAM ERROR DOLOR, PERFERENDIS DOLOREM RERUM DOLOREMQUE PORRO TEMPORE NOSTRUM SOLUTA AUT OBCAECATI MODI ISTE EVENIET ITAQUE CORPORIS QUO, RATIONE SIT IPSUM! ALIAS HARUM ASPERIORES, QUAE QUIA IURE IMPEDIT INVENTORE IUSTO QUO AB EAQUE EXPEDITA QUAM VOLUPTATIBUS. ET CONSEQUUNTUR NAM ANIMI ITAQUE REPELLAT LABORIOSAM EARUM VOLUPTATIBUS. ACCUSAMUS QUI POSSIMUS DUCIMUS CONSEQUUNTUR PORRO, RERUM QUAERAT, CORPORIS IPSUM DOLORE QUISQUAM EXERCITATIONEM IPSA A PARIATUR NATUS FUGA SEQUI. CONSEQUUNTUR ENIM NATUS EUM REPELLENDUS MAXIME. ISTE FUGA VOLUPTATIBUS CONSEQUUNTUR, VERITATIS REM ACCUSANTIUM CUMQUE EARUM QUIS RATIONE VERO PORRO, MINIMA NATUS, BEATAE EST! ACCUSANTIUM MAGNI AUTEM ODIT QUIS EARUM NEQUE VOLUPTAS TENETUR MOLLITIA DOLOREM MAIORES EIUS DIGNISSIMOS ID DELECTUS NUMQUAM, CONSEQUUNTUR ODIO IMPEDIT QUOS VERO CUMQUE QUOD ASPERIORES NECESSITATIBUS NAM DISTINCTIO SEQUI. IUSTO MOLESTIAE MAXIME FUGIAT TEMPORIBUS ADIPISCI EX MOLLITIA OPTIO SEQUI VOLUPTATE! EIUS ADIPISCI TEMPORIBUS NIHIL SAEPE ID NECESSITATIBUS QUIA DOLORIBUS. EX ANIMI NEQUE TENETUR IPSAM, REPREHENDERIT ALIQUID VITAE CUM EVENIET DOLORIBUS DOLOREM VOLUPTATIBUS DISTINCTIO IMPEDIT NEMO ALIQUAM? OBCAECATI IMPEDIT RECUSANDAE DISTINCTIO EOS MOLESTIAE SOLUTA VERO CULPA QUIS NON, TOTAM DOLORIBUS. DESERUNT NULLA OFFICIIS ALIAS VITAE. BLANDITIIS VERITATIS ALIAS SINT COMMODI MINUS, CUM QUOS ATQUE MOLESTIAS AUT EIUS NOSTRUM DOLORES DOLORE DISTINCTIO NEQUE ILLO AB ALIQUAM AT VEL. ACCUSAMUS MAIORES QUAERAT REM, ASPERIORES DOLORES PRAESENTIUM AUT, VOLUPTATE CONSEQUUNTUR TENETUR SINT, CONSECTETUR LABORIOSAM! OFFICIA DOLORE QUIDEM ADIPISCI ILLO MINIMA FUGA, REPELLENDUS UT ARCHITECTO FACILIS MAXIME MOLESTIAE, PARIATUR REPELLAT NAM DOLOR EARUM CUPIDITATE. VENIAM RERUM PORRO ILLO ISTE TOTAM CONSEQUUNTUR IUSTO VOLUPTATE ET CULPA. SEQUI AT SOLUTA NUMQUAM LAUDANTIUM? QUO ENIM ARCHITECTO ASPERNATUR BEATAE, CORRUPTI DELENITI? DOLOREMQUE SUNT PARIATUR OMNIS OPTIO AUT DUCIMUS INCIDUNT IMPEDIT, HIC ET CONSEQUATUR PLACEAT ID IPSAM ILLUM NOBIS! SIT VERITATIS REPUDIANDAE REPREHENDERIT CONSECTETUR DOLOREM ESSE NAM LAUDANTIUM ASPERNATUR IN TENETUR INCIDUNT NESCIUNT QUAERAT HIC PERFERENDIS DOLORIBUS PRAESENTIUM DEBITIS DESERUNT, IPSAM INVENTORE ANIMI ACCUSANTIUM ET VOLUPTATEM! PLACEAT TEMPORA NAM NIHIL. QUAERAT EST NUMQUAM QUAE DOLORIBUS QUIS DOLORES MAIORES ET EXCEPTURI NESCIUNT REM DELENITI, QUAS REPELLAT OMNIS QUIBUSDAM."
echo "-----------------------------------------------------------------------"