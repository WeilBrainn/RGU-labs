#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "task2.h"

// Структура Address
typedef struct Address {
    String city;
    String street;
    int house_number;
    String building;
    int apartment_number;
    String postal_code; // Из 6 символов
} Address;

// Структура Mail
typedef struct Mail {
    Address recipient_address;
    double weight;
    String mail_id; // Из 14 символов
    String creation_time;
    String delivery_time;
} Mail;

// Структура Post
typedef struct Post {
    Address *office_address;
    Mail *mails;
    size_t mail_count;
} Post;

// Вспомогательные функции
int validate_address(const Address *address) {
    if (address == NULL || address->city.array == NULL || address->street.array == NULL ||
        address->postal_code.array == NULL || address->postal_code.length != 6 || address->house_number <= 0 ||
        address->apartment_number <= 0) {
        return 0; // Неверный адрес
    }
    return 1;
}

int validate_mail(const Mail *mail) {
    if (!validate_address(&mail->recipient_address) || mail->weight < 0 ||
        mail->mail_id.array == NULL || mail->mail_id.length != 14) {
        return 0; // Неверная посылка
    }
    return 1;
}

// Функция для добавления Mail в Post
void add_mail(Post *post, const Mail *mail) {
    if (!validate_mail(mail)) {
        printf("Invalid mail data.\n");
        return;
    }

    post->mails = realloc(post->mails, (post->mail_count + 1) * sizeof(Mail));
    if (post->mails == NULL) {
        printf("Memory allocation error.\n");
        return;
    }
    post->mails[post->mail_count] = *mail;
    post->mail_count++;
}

// Функция для удаления Mail по идентификатору
void delete_mail(Post *post, const char *mail_id) {
    for (size_t i = 0; i < post->mail_count; i++) {
        if (strcmp(post->mails[i].mail_id.array, mail_id) == 0) {
            // Освобождение памяти строки
            clearString(&post->mails[i].mail_id);
            clearString(&post->mails[i].creation_time);
            clearString(&post->mails[i].delivery_time);
            clearString(&post->mails[i].recipient_address.city);
            clearString(&post->mails[i].recipient_address.street);
            clearString(&post->mails[i].recipient_address.building);
            clearString(&post->mails[i].recipient_address.postal_code);

            // Сдвиг оставшихся элементов
            for (size_t j = i; j < post->mail_count - 1; j++) {
                post->mails[j] = post->mails[j + 1];
            }
            post->mail_count--;
            post->mails = realloc(post->mails, post->mail_count * sizeof(Mail));
            return;
        }
    }
    printf("Mail with ID %s not found.\n", mail_id);
}

// Функция для поиска Mail по идентификатору
void find_mail_by_id(const Post *post, const char *mail_id) {
    for (size_t i = 0; i < post->mail_count; i++) {
        if (strcmp(post->mails[i].mail_id.array, mail_id) == 0) {
            printf("Mail found:\n");
            printf("Recipient City: %s\n", post->mails[i].recipient_address.city.array);
            printf("Weight: %.2f\n", post->mails[i].weight);
            printf("Created: %s\n", post->mails[i].creation_time.array);
            printf("Delivery: %s\n", post->mails[i].delivery_time.array);
            return;
        }
    }
    printf("Mail with ID %s not found.\n", mail_id);
}

// Функция сортировки Mail по индексу и идентификатору
int compare_mail(const void *a, const void *b) {
    const Mail *mail1 = (const Mail *)a;
    const Mail *mail2 = (const Mail *)b;

    int postal_cmp = strcmp(mail1->recipient_address.postal_code.array, mail2->recipient_address.postal_code.array);
    if (postal_cmp != 0) {
        return postal_cmp;
    }
    return strcmp(mail1->mail_id.array, mail2->mail_id.array);
}

void sort_mails(Post *post) {
    qsort(post->mails, post->mail_count, sizeof(Mail), compare_mail);
}

// Главная функция
int main() {
    Post post_office = {0};
    post_office.mails = NULL;
    post_office.mail_count = 0;

    printf("Interactive Mail System:\n");
    printf("1. Add Mail\n");
    printf("2. Delete Mail\n");
    printf("3. Find Mail by ID\n");
    printf("4. Exit\n");

    int choice;
    char buffer[256];
    while (1) {
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // Очистка ввода

        switch (choice) {
        case 1:
            ;
            Mail mail;
            printf("Enter recipient city: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            instance(buffer, &mail.recipient_address.city);

            printf("Enter weight: ");
            scanf("%lf", &mail.weight);
            getchar();

            printf("Enter mail ID: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            instance(buffer, &mail.mail_id);

            add_mail(&post_office, &mail);
            sort_mails(&post_office);
            break;

        case 2:
            printf("Enter mail ID to delete: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            delete_mail(&post_office, buffer);
            break;

        case 3:
            printf("Enter mail ID to search: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            find_mail_by_id(&post_office, buffer);
            break;

        case 4:
            printf("Exiting system.\n");
            for (size_t i = 0; i < post_office.mail_count; i++) {
                clearString(&post_office.mails[i].mail_id);
                clearString(&post_office.mails[i].creation_time);
                clearString(&post_office.mails[i].delivery_time);
                clearString(&post_office.mails[i].recipient_address.city);
                clearString(&post_office.mails[i].recipient_address.street);
                clearString(&post_office.mails[i].recipient_address.building);
                clearString(&post_office.mails[i].recipient_address.postal_code);
            }
            free(post_office.mails);
            return 0;

        default:
            printf("Invalid choice.\n");
        }
    }
}
